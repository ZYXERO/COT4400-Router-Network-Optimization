/*
 * ============================================================
 * File:    kruskal.cpp
 * Project: Internet Router Network Optimization
 * Course:  COT-4400 Analysis of Algorithms — USF Bellini College
 * Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
 * ============================================================
 *
 * Description:
 *   Implements Kruskal's Minimum Spanning Tree (MST) algorithm.
 *
 *   NOTE: MST is computed on the UNDIRECTED version of the graph.
 *   Each directed edge (u, v, w) is treated as an undirected link
 *   for MST purposes. This is meaningful in a network context for
 *   finding the minimum total latency backbone.
 *
 *   Uses Union-Find (Disjoint Set Union) with:
 *     - Path Compression: flattens the tree for O(α) find operations
 *     - Union by Rank:    keeps the tree balanced during merges
 *
 *   Algorithm:
 *     1. Sort all edges by weight ascending
 *     2. Greedily add each edge to MST if it doesn't form a cycle
 *     3. Stop when MST has V-1 edges (spanning tree complete)
 * ============================================================
 */

#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm> // std::sort for edges
#include <string>
#include <tuple>

// ============================================================
// Union-Find (Disjoint Set Union) Data Structure
// ============================================================

/*
 * UnionFind
 * Purpose:  Efficiently tracks connected components (sets) during
 *           MST construction. Supports two operations:
 *             find(x)        — returns the representative of x's set
 *             unite(x, y)    — merges the sets containing x and y
 *
 * Optimizations:
 *   Path Compression (find): makes all nodes point directly to root,
 *                            giving near O(1) future find operations.
 *   Union by Rank (unite):   attaches smaller-rank tree under larger,
 *                            keeping the tree depth minimal.
 *
 * Time Complexity: O(α(V)) amortized per operation, where α is the
 *                  inverse Ackermann function (effectively constant).
 * Space Complexity: O(V)
 */
struct UnionFind {
    std::vector<int> parent; // parent[i] = representative of set containing i
    std::vector<int> rank;   // rank[i] = upper bound on tree height at i

    // --------------------------------------------------------
    // Constructor: each vertex starts as its own component
    // --------------------------------------------------------
    explicit UnionFind(int numVertices)
        : parent(numVertices), rank(numVertices, 0) {
        for (int i = 0; i < numVertices; ++i) {
            parent[i] = i; // Each router is its own root initially
        }
    }

    // --------------------------------------------------------
    // find
    // Purpose: Returns the root representative of the set containing x.
    //          Applies path compression: makes x point directly to root.
    // Time:    O(α(V)) amortized — effectively O(1)
    // --------------------------------------------------------
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression (recursive)
        }
        return parent[x];
    }

    // --------------------------------------------------------
    // unite
    // Purpose: Merges the sets containing x and y using union by rank.
    //          Returns true if x and y were in different sets (merge occurred).
    //          Returns false if x and y were already in the same set (cycle).
    // Time:    O(α(V)) amortized
    // --------------------------------------------------------
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return false; // Already in the same set — adding edge would form cycle
        }

        // Union by Rank: attach smaller rank tree under larger rank tree
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            // Equal rank: arbitrary choice, increment rank of new root
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        return true; // Merge successful
    }
};

// ============================================================
// Kruskal's MST Algorithm
// ============================================================

/*
 * kruskal
 * Purpose:     Finds the Minimum Spanning Tree (MST) of the router
 *              network, treating all directed edges as undirected.
 *              The MST represents the minimum total latency backbone
 *              needed to connect all routers.
 *
 *              Uses Union-Find for efficient cycle detection during
 *              greedy edge selection.
 *
 * Params:      g — the directed weighted graph (edges treated as undirected)
 *
 * Time Complexity:  O(E log E)
 *   — Sorting edges: O(E log E)
 *   — Union-Find operations: O(E * α(V)) ≈ O(E)
 *   — Total dominated by sort: O(E log E)
 *
 * Space Complexity: O(V)
 *   — Union-Find parent[] and rank[] arrays: O(V)
 *   — MST edge list: O(V) — at most V-1 edges in the tree
 *
 * Note: MST is computed on the UNDIRECTED version of the graph.
 */
void kruskal(Graph& g) {
    std::cout << "\n=== Kruskal's Minimum Spanning Tree ===\n";
    std::cout << "NOTE: MST computed on undirected version of the graph.\n";
    std::cout << "Time Complexity:  O(E log E)\n";
    std::cout << "Space Complexity: O(V)\n\n";

    // Create a copy of the edge list sorted by weight ascending
    // edgeList entries are (weight, u, v)
    std::vector<std::tuple<int, int, int>> sortedEdges = g.edgeList;
    std::sort(sortedEdges.begin(), sortedEdges.end());

    // Initialize Union-Find for cycle detection
    UnionFind uf(g.numVertices);

    // MST edge collection and total weight accumulator
    std::vector<std::tuple<int, int, int>> mstEdges;
    int totalMSTWeight = 0;

    // The MST of V vertices contains exactly V-1 edges
    const int targetEdgesInMST = g.numVertices - 1;

    // Greedily process edges in ascending weight order
    for (const auto& edgeTuple : sortedEdges) {
        int weight = std::get<0>(edgeTuple);
        int u      = std::get<1>(edgeTuple);
        int v      = std::get<2>(edgeTuple);

        // Attempt to add edge (u, v) to MST
        // unite() returns false if u and v are already connected (cycle)
        if (uf.unite(u, v)) {
            mstEdges.emplace_back(weight, u, v);
            totalMSTWeight += weight;

            // Stop early once we have V-1 edges in the MST
            if (static_cast<int>(mstEdges.size()) == targetEdgesInMST) {
                break;
            }
        }
    }

    // Print MST results
    std::cout << "MST Edges (sorted by inclusion order):\n";
    std::cout << std::string(50, '-') << "\n";
    std::cout << "Edge              | Weight (ms)\n";
    std::cout << std::string(50, '-') << "\n";

    for (const auto& edge : mstEdges) {
        int weight = std::get<0>(edge);
        int u      = std::get<1>(edge);
        int v      = std::get<2>(edge);
        std::cout << "R" << u << " -- R" << v
                  << "          | " << weight << "ms\n";
    }

    std::cout << std::string(50, '-') << "\n";
    std::cout << "Total MST edges:  " << mstEdges.size() << "\n";
    std::cout << "Total MST weight: " << totalMSTWeight << "ms\n";

    // Verify MST is complete (spanning tree covers all vertices)
    if (static_cast<int>(mstEdges.size()) < targetEdgesInMST) {
        std::cout << "\nWARNING: Graph is disconnected — MST is a Minimum Spanning Forest.\n";
        std::cout << "Only " << mstEdges.size() << " of "
                  << targetEdgesInMST << " required edges found.\n";
    }
}
