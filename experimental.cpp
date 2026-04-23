/*
 * ============================================================
 * File:    experimental.cpp
 * Project: Internet Router Network Optimization
 * Course:  COT-4400 Analysis of Algorithms — USF Bellini College
 * Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
 * ============================================================
 *
 * Description:
 *   Implements the experimental analysis module for comparing
 *   algorithm performance across different graph sizes and densities.
 *
 *   Four graph scenarios are tested:
 *     a) Small Sparse  — 10 nodes, ~15 edges
 *     b) Small Dense   — 10 nodes, ~40 edges
 *     c) Large Sparse  — 50 nodes, ~75 edges
 *     d) Large Dense   — 50 nodes, ~600 edges
 *
 *   Each algorithm (BFS, DFS, Dijkstra, Bellman-Ford, Kruskal) is timed
 *   using std::chrono::high_resolution_clock for precision measurement.
 *   Results are printed in a formatted comparison table (in microseconds).
 * ============================================================
 */

#include "graph.h"
#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>  // std::setw, std::left for table formatting
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <tuple>

// ============================================================
// Silent Algorithm Variants (No Console Output for Timing)
// ============================================================
// These local versions suppress all cout output so that the timer
// measures only computation time, not I/O time.

/*
 * silentBFS
 * Purpose:     BFS traversal with output suppressed for timing.
 * Time:        O(V + E)
 */
static void silentBFS(const Graph& g, int source) {
    std::vector<bool> visited(g.numVertices, false);
    std::queue<int> bfsQueue;
    visited[source] = true;
    bfsQueue.push(source);
    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        for (const auto& edge : g.adjList[current]) {
            int neighbor = edge.first;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                bfsQueue.push(neighbor);
            }
        }
    }
}

/*
 * silentDFSHelper
 * Purpose:     Recursive DFS helper with output suppressed.
 */
static void silentDFSHelper(const Graph& g, int vertex,
                             std::vector<bool>& visited) {
    visited[vertex] = true;
    for (const auto& edge : g.adjList[vertex]) {
        int neighbor = edge.first;
        if (!visited[neighbor]) {
            silentDFSHelper(g, neighbor, visited);
        }
    }
}

/*
 * silentDFS
 * Purpose:     DFS traversal with output suppressed for timing.
 * Time:        O(V + E)
 */
static void silentDFS(const Graph& g, int source) {
    std::vector<bool> visited(g.numVertices, false);
    silentDFSHelper(g, source, visited);
    for (int i = 0; i < g.numVertices; ++i) {
        if (!visited[i]) {
            silentDFSHelper(g, i, visited);
        }
    }
}

/*
 * silentDijkstra
 * Purpose:     Dijkstra's algorithm with output suppressed for timing.
 * Time:        O((V + E) log V)
 */
static void silentDijkstra(const Graph& g, int source) {
    std::vector<int> dist(g.numVertices, INT_MAX);
    using PQEntry = std::pair<int, int>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> minHeap;
    dist[source] = 0;
    minHeap.push({0, source});
    while (!minHeap.empty()) {
        auto [currentDist, currentRouter] = minHeap.top();
        minHeap.pop();
        if (currentDist > dist[currentRouter]) continue;
        for (const auto& edge : g.adjList[currentRouter]) {
            int neighbor   = edge.first;
            int edgeWeight = edge.second;
            int newDist    = dist[currentRouter] + edgeWeight;
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                minHeap.push({newDist, neighbor});
            }
        }
    }
}

/*
 * silentBellmanFord
 * Purpose:     Bellman-Ford with output suppressed for timing.
 * Time:        O(V * E)
 */
static void silentBellmanFord(const Graph& g, int source) {
    std::vector<int> dist(g.numVertices, INT_MAX);
    dist[source] = 0;
    for (int pass = 1; pass <= g.numVertices - 1; ++pass) {
        bool relaxed = false;
        for (const auto& edgeTuple : g.edgeList) {
            int w = std::get<0>(edgeTuple);
            int u = std::get<1>(edgeTuple);
            int v = std::get<2>(edgeTuple);
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                relaxed = true;
            }
        }
        if (!relaxed) break;
    }
}

/*
 * silentKruskal
 * Purpose:     Kruskal's MST with output suppressed for timing.
 * Time:        O(E log E)
 */
static void silentKruskal(Graph& g) {
    std::vector<std::tuple<int, int, int>> sortedEdges = g.edgeList;
    std::sort(sortedEdges.begin(), sortedEdges.end());

    // Inline Union-Find for silence (no struct needed outside)
    std::vector<int> parent(g.numVertices);
    std::vector<int> rank(g.numVertices, 0);
    for (int i = 0; i < g.numVertices; ++i) parent[i] = i;

    // Path-compressed find
    std::function<int(int)> findRoot = [&](int x) -> int {
        if (parent[x] != x) parent[x] = findRoot(parent[x]);
        return parent[x];
    };

    int mstCount = 0;
    int targetEdges = g.numVertices - 1;

    for (const auto& edgeTuple : sortedEdges) {
        int u = std::get<1>(edgeTuple);
        int v = std::get<2>(edgeTuple);
        int rootU = findRoot(u);
        int rootV = findRoot(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else { parent[rootV] = rootU; rank[rootU]++; }
            if (++mstCount == targetEdges) break;
        }
    }
}

// ============================================================
// Graph Generator Helpers
// ============================================================

/*
 * buildSparseGraph
 * Purpose:     Creates a graph with approximately (nodes * 1.5) edges
 *              chained in a sparse pattern (path + a few cross-links).
 * Time:        O(nodes)
 */
static Graph buildSparseGraph(int nodes) {
    Graph g(nodes);
    // Create a linear chain to ensure connectivity
    for (int i = 0; i < nodes - 1; ++i) {
        g.addEdge(i, i + 1, (i % 10) + 1); // weights 1–10 ms
    }
    // Add a few skip-connections for sparsity beyond a pure path
    for (int i = 0; i < nodes - 3; i += 3) {
        g.addEdge(i, i + 3, (i % 15) + 5); // every 3rd node shortcut
    }
    return g;
}

/*
 * buildDenseGraph
 * Purpose:     Creates a graph with approximately nodes*(nodes-1)/2 edges,
 *              representing a dense, nearly-complete network topology.
 * Time:        O(nodes^2)
 */
static Graph buildDenseGraph(int nodes) {
    Graph g(nodes);
    // Add directed edges from each node to most others (dense)
    for (int i = 0; i < nodes; ++i) {
        for (int j = i + 1; j < nodes; ++j) {
            g.addEdge(i, j, (i + j) % 20 + 1); // weights 1–20 ms
        }
    }
    return g;
}

// ============================================================
// Timer Helper
// ============================================================

/*
 * measureTime
 * Purpose:     Measures wall-clock execution time of a function call.
 * Template:    Func — any callable (lambda, function pointer, etc.)
 * Returns:     Elapsed time in microseconds (double)
 * Time:        O(1) overhead beyond the measured function
 */
template<typename Func>
static double measureTime(Func&& func) {
    auto startTime = std::chrono::high_resolution_clock::now();
    func(); // Execute the algorithm being timed
    auto endTime   = std::chrono::high_resolution_clock::now();

    // Convert duration to microseconds for precision at small sizes
    std::chrono::duration<double, std::micro> elapsed = endTime - startTime;
    return elapsed.count();
}

// ============================================================
// Experimental Analysis
// ============================================================

/*
 * runExperiments
 * Purpose:     Benchmarks each algorithm across four graph scenarios:
 *                a) Small Sparse  — 10 nodes, ~15 edges
 *                b) Small Dense   — 10 nodes, ~45 edges
 *                c) Large Sparse  — 50 nodes, ~75 edges
 *                d) Large Dense   — 50 nodes, ~1225 edges
 *
 *              Measures execution time using high_resolution_clock
 *              and prints a formatted comparison table.
 *
 * Time Complexity:  Varies by algorithm and graph size (see individual notes)
 * Space Complexity: O(V + E) per graph scenario
 */
void runExperiments() {
    std::cout << "\n=== Experimental Performance Analysis ===\n";
    std::cout << "Timing unit: microseconds (μs)\n";
    std::cout << "Source node: 0 for all traversal/SSSP algorithms\n\n";

    // --------------------------------------------------------
    // Build the four test graph scenarios
    // --------------------------------------------------------
    Graph smallSparse = buildSparseGraph(10);   // ~15 edges
    Graph smallDense  = buildDenseGraph(10);    // ~45 edges
    Graph largeSparse = buildSparseGraph(50);   // ~75 edges
    Graph largeDense  = buildDenseGraph(50);    // ~1225 edges

    // Print graph stats for context
    std::cout << "Graph Sizes:\n";
    std::cout << "  Small Sparse: " << smallSparse.numVertices << " nodes, "
              << smallSparse.edgeList.size() << " edges\n";
    std::cout << "  Small Dense:  " << smallDense.numVertices  << " nodes, "
              << smallDense.edgeList.size()  << " edges\n";
    std::cout << "  Large Sparse: " << largeSparse.numVertices << " nodes, "
              << largeSparse.edgeList.size() << " edges\n";
    std::cout << "  Large Dense:  " << largeDense.numVertices  << " nodes, "
              << largeDense.edgeList.size()  << " edges\n\n";

    // --------------------------------------------------------
    // Algorithm names for table display
    // --------------------------------------------------------
    const std::vector<std::string> algorithmNames = {
        "BFS", "DFS", "Dijkstra", "Bellman-Ford", "Kruskal"
    };

    // --------------------------------------------------------
    // Measure each algorithm on each scenario
    // Results stored as: times[algorithm][scenario]
    // --------------------------------------------------------
    const int NUM_ALGORITHMS = 5;
    const int NUM_SCENARIOS  = 4;
    double times[NUM_ALGORITHMS][NUM_SCENARIOS];

    // BFS (index 0)
    times[0][0] = measureTime([&](){ silentBFS(smallSparse, 0); });
    times[0][1] = measureTime([&](){ silentBFS(smallDense,  0); });
    times[0][2] = measureTime([&](){ silentBFS(largeSparse, 0); });
    times[0][3] = measureTime([&](){ silentBFS(largeDense,  0); });

    // DFS (index 1)
    times[1][0] = measureTime([&](){ silentDFS(smallSparse, 0); });
    times[1][1] = measureTime([&](){ silentDFS(smallDense,  0); });
    times[1][2] = measureTime([&](){ silentDFS(largeSparse, 0); });
    times[1][3] = measureTime([&](){ silentDFS(largeDense,  0); });

    // Dijkstra (index 2)
    times[2][0] = measureTime([&](){ silentDijkstra(smallSparse, 0); });
    times[2][1] = measureTime([&](){ silentDijkstra(smallDense,  0); });
    times[2][2] = measureTime([&](){ silentDijkstra(largeSparse, 0); });
    times[2][3] = measureTime([&](){ silentDijkstra(largeDense,  0); });

    // Bellman-Ford (index 3)
    times[3][0] = measureTime([&](){ silentBellmanFord(smallSparse, 0); });
    times[3][1] = measureTime([&](){ silentBellmanFord(smallDense,  0); });
    times[3][2] = measureTime([&](){ silentBellmanFord(largeSparse, 0); });
    times[3][3] = measureTime([&](){ silentBellmanFord(largeDense,  0); });

    // Kruskal (index 4)
    times[4][0] = measureTime([&](){ silentKruskal(smallSparse); });
    times[4][1] = measureTime([&](){ silentKruskal(smallDense);  });
    times[4][2] = measureTime([&](){ silentKruskal(largeSparse); });
    times[4][3] = measureTime([&](){ silentKruskal(largeDense);  });

    // --------------------------------------------------------
    // Print Results Table
    // --------------------------------------------------------
    const int COL_W = 15; // Column width for alignment
    const int ALG_W = 14; // Algorithm name column width

    std::cout << std::left
              << std::setw(ALG_W) << "Algorithm"
              << "| " << std::setw(COL_W) << "Small Sparse"
              << "| " << std::setw(COL_W) << "Small Dense"
              << "| " << std::setw(COL_W) << "Large Sparse"
              << "| " << std::setw(COL_W) << "Large Dense"
              << "\n";

    std::cout << std::string(ALG_W + (COL_W + 2) * NUM_SCENARIOS, '-') << "\n";

    for (int a = 0; a < NUM_ALGORITHMS; ++a) {
        std::cout << std::left << std::setw(ALG_W) << algorithmNames[a];
        for (int s = 0; s < NUM_SCENARIOS; ++s) {
            // Format time with 3 decimal places + unit label
            std::ostringstream timeStr;
            timeStr << std::fixed << std::setprecision(3) << times[a][s] << "μs";
            std::cout << "| " << std::setw(COL_W) << timeStr.str();
        }
        std::cout << "\n";
    }

    std::cout << std::string(ALG_W + (COL_W + 2) * NUM_SCENARIOS, '-') << "\n";
    std::cout << "\nKey Observations:\n";
    std::cout << "  - BFS/DFS are fastest (simple traversal, O(V+E))\n";
    std::cout << "  - Dijkstra is efficient for sparse graphs (O((V+E) log V))\n";
    std::cout << "  - Bellman-Ford is slowest on dense graphs (O(V*E))\n";
    std::cout << "  - Kruskal scales with edges (O(E log E))\n";
}
