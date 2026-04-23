/*
 * ============================================================
 * File:    bfs_dfs.cpp
 * Project: Internet Router Network Optimization
 * Course:  COT-4400 Analysis of Algorithms — USF Bellini College
 * Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
 * ============================================================
 *
 * Description:
 *   Implements Breadth-First Search (BFS) and Depth-First Search (DFS)
 *   traversal algorithms on the router network graph.
 *
 *   BFS explores routers level by level (uses a queue).
 *   DFS explores as deep as possible before backtracking (uses recursion).
 * ============================================================
 */

#include "graph.h"
#include <iostream>
#include <vector>
#include <queue>

// ============================================================
// DFS Helper (Recursive)
// ============================================================

/*
 * dfsHelper
 * Purpose:     Recursive DFS utility that visits a vertex and
 *              all unvisited neighbors, tracking discovery order.
 * Params:      g       — the graph
 *              vertex  — current router being visited
 *              visited — boolean array tracking visited routers
 *              order   — counter tracking visit sequence number
 * Time:        O(V + E) across all recursive calls
 * Space:       O(V) on the call stack (worst-case depth = V)
 */
static void dfsHelper(const Graph& g, int vertex,
                      std::vector<bool>& visited, int& order) {
    // Mark current router as visited
    visited[vertex] = true;
    std::cout << "  [" << order++ << "] Visited R" << vertex << "\n";

    // Recurse into each unvisited neighbor
    for (const auto& edge : g.adjList[vertex]) {
        int neighbor = edge.first;
        if (!visited[neighbor]) {
            dfsHelper(g, neighbor, visited, order);
        }
    }
}

// ============================================================
// BFS Algorithm
// ============================================================

/*
 * BFS — Breadth-First Search
 * Purpose:     Explores the router network layer by layer starting
 *              from the source router. Useful for finding shortest
 *              hop-count paths in unweighted scenarios.
 *
 *              Uses a queue (FIFO) to process routers in the order
 *              they are discovered.
 *
 * Params:      g      — the directed weighted graph of routers
 *              source — starting router index (0-indexed)
 *
 * Time Complexity:  O(V + E)
 *   — Each vertex is enqueued and dequeued exactly once: O(V)
 *   — Each edge is inspected once: O(E)
 *
 * Space Complexity: O(V)
 *   — visited[] array: O(V)
 *   — queue holds at most V elements: O(V)
 */
void BFS(const Graph& g, int source) {
    std::cout << "\n=== BFS Traversal from R" << source << " ===\n";
    std::cout << "Time Complexity:  O(V + E)\n";
    std::cout << "Space Complexity: O(V)\n\n";

    // Track which routers have been visited to avoid re-processing
    std::vector<bool> visited(g.numVertices, false);

    // Standard FIFO queue for BFS exploration
    std::queue<int> bfsQueue;

    // Initialize: visit the source router
    visited[source] = true;
    bfsQueue.push(source);

    int visitOrder = 1; // Counter to show discovery sequence

    std::cout << "Visit Order:\n";

    while (!bfsQueue.empty()) {
        // Dequeue the front router and process it
        int currentRouter = bfsQueue.front();
        bfsQueue.pop();

        std::cout << "  [" << visitOrder++ << "] Visited R"
                  << currentRouter << "\n";

        // Enqueue all unvisited neighbors of the current router
        for (const auto& edge : g.adjList[currentRouter]) {
            int neighbor = edge.first;
            if (!visited[neighbor]) {
                visited[neighbor] = true;   // Mark immediately on enqueue
                bfsQueue.push(neighbor);    // to prevent duplicate enqueuing
            }
        }
    }

    // Report any routers unreachable from the source
    std::cout << "\nRouters unreachable from R" << source << ": ";
    bool anyUnreachable = false;
    for (int i = 0; i < g.numVertices; ++i) {
        if (!visited[i]) {
            std::cout << "R" << i << " ";
            anyUnreachable = true;
        }
    }
    if (!anyUnreachable) {
        std::cout << "None (all routers reachable)";
    }
    std::cout << "\n";
}

// ============================================================
// DFS Algorithm
// ============================================================

/*
 * DFS — Depth-First Search
 * Purpose:     Explores the router network as deeply as possible
 *              along each path before backtracking. Handles
 *              disconnected components by restarting DFS from
 *              any unvisited router after each component is exhausted.
 *
 *              Uses recursion (implicit call stack as DFS stack).
 *
 * Params:      g      — the directed weighted graph of routers
 *              source — starting router index (0-indexed)
 *
 * Time Complexity:  O(V + E)
 *   — Each vertex is visited exactly once: O(V)
 *   — Each edge is examined once per vertex: O(E)
 *
 * Space Complexity: O(V)
 *   — visited[] array: O(V)
 *   — Recursive call stack depth up to O(V) in worst case
 */
void DFS(const Graph& g, int source) {
    std::cout << "\n=== DFS Traversal from R" << source << " ===\n";
    std::cout << "Time Complexity:  O(V + E)\n";
    std::cout << "Space Complexity: O(V)\n\n";

    // Track which routers have been visited
    std::vector<bool> visited(g.numVertices, false);

    int visitOrder = 1; // Counter to show discovery sequence

    std::cout << "Visit Order:\n";

    // Start DFS from the specified source router
    dfsHelper(g, source, visited, visitOrder);

    // Handle disconnected components: if any router is still unvisited,
    // start DFS from it to ensure full traversal coverage
    for (int i = 0; i < g.numVertices; ++i) {
        if (!visited[i]) {
            std::cout << "  [Component] Starting DFS from disconnected R"
                      << i << "\n";
            dfsHelper(g, i, visited, visitOrder);
        }
    }

    std::cout << "\nDFS complete. Total routers visited: "
              << (visitOrder - 1) << "/" << g.numVertices << "\n";
}
