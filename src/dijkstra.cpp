/*
 * ============================================================
 * File:    dijkstra.cpp
 * Project: Internet Router Network Optimization
 * Course:  COT-4400 Analysis of Algorithms — USF Bellini College
 * Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
 * ============================================================
 *
 * Description:
 *   Implements Dijkstra's Single-Source Shortest Path algorithm.
 *
 *   IMPORTANT: Dijkstra's algorithm does NOT support negative
 *   edge weights. All latency values in the router network are
 *   positive, so this algorithm is safe to use here.
 *
 *   Uses a min-heap priority queue for efficient extraction of the
 *   router with the current minimum tentative distance.
 * ============================================================
 */

#include "graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>   // INT_MAX for infinity representation
#include <string>
#include <algorithm> // std::reverse for path reconstruction

// Symbolic constant for "no previous node" in path reconstruction
static const int NO_PREDECESSOR = -1;

// ============================================================
// Path reconstruction helper
// ============================================================

/*
 * reconstructPath
 * Purpose:     Traces back through the prev[] array from destination
 *              to source to reconstruct the shortest path taken.
 * Params:      prev — predecessor array built during Dijkstra
 *              dest — destination router index
 * Returns:     Vector of router indices forming the path (source -> dest)
 * Time:        O(V) — path length at most V vertices
 */
static std::vector<int> reconstructPath(const std::vector<int>& prev, int dest) {
    std::vector<int> path;
    for (int node = dest; node != NO_PREDECESSOR; node = prev[node]) {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// ============================================================
// Dijkstra's Algorithm
// ============================================================

/*
 * dijkstra
 * Purpose:     Finds the shortest path (minimum latency) from the
 *              source router to ALL other routers in the network.
 *              Uses a min-heap priority queue (greedy approach).
 *
 *              NOTE: Does NOT support negative edge weights.
 *              All edge weights must be >= 0 for correctness.
 *
 * Params:      g      — the directed weighted graph of routers
 *              source — starting router index (0-indexed)
 *
 * Time Complexity:  O((V + E) log V)
 *   — Each vertex is extracted from the heap once: O(V log V)
 *   — Each edge triggers at most one heap insertion: O(E log V)
 *   — Total: O((V + E) log V)
 *
 * Space Complexity: O(V)
 *   — dist[]  — shortest distance array: O(V)
 *   — prev[]  — predecessor array: O(V)
 *   — Priority queue holds at most E entries: O(E), but typically O(V)
 */
void dijkstra(const Graph& g, int source) {
    std::cout << "\n=== Dijkstra's Shortest Path from R" << source << " ===\n";
    std::cout << "NOTE: Does NOT support negative edge weights.\n";
    std::cout << "Time Complexity:  O((V + E) log V)\n";
    std::cout << "Space Complexity: O(V)\n\n";

    const int INFINITY_DIST = INT_MAX; // Represents unreachable routers

    // dist[v] = shortest known distance from source to router v
    std::vector<int> dist(g.numVertices, INFINITY_DIST);

    // prev[v] = predecessor of v on the shortest path from source
    std::vector<int> prev(g.numVertices, NO_PREDECESSOR);

    /*
     * Min-heap priority queue: (distance, vertex)
     * Using greater<> makes it a min-heap (default is max-heap).
     * Pairs are compared lexicographically, so distance is the primary key.
     */
    using PQEntry = std::pair<int, int>; // (distance, router_index)
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> minHeap;

    // Initialize: source router has distance 0 from itself
    dist[source] = 0;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        // Extract the router with the smallest tentative distance
        auto [currentDist, currentRouter] = minHeap.top();
        minHeap.pop();

        /*
         * Lazy deletion: if we have already found a shorter path to
         * currentRouter, skip this stale entry in the heap.
         */
        if (currentDist > dist[currentRouter]) {
            continue;
        }

        // Relax all outgoing edges from currentRouter
        for (const auto& edge : g.adjList[currentRouter]) {
            int neighbor = edge.first;
            int edgeWeight = edge.second; // latency in ms

            int newDist = dist[currentRouter] + edgeWeight;

            // If a shorter path to neighbor is found, update and re-enqueue
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                prev[neighbor] = currentRouter;
                minHeap.push({newDist, neighbor});
            }
        }
    }

    // Print results: shortest distance and path for each destination router
    std::cout << "Results (Source: R" << source << "):\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << "Destination | Latency (ms) | Path\n";
    std::cout << std::string(60, '-') << "\n";

    for (int dest = 0; dest < g.numVertices; ++dest) {
        std::cout << "R" << dest << "          | ";

        if (dist[dest] == INFINITY_DIST) {
            // No path exists from source to this router
            std::cout << "UNREACHABLE   | N/A\n";
        } else {
            std::cout << dist[dest] << "ms           | ";

            // Reconstruct and print the path
            std::vector<int> path = reconstructPath(prev, dest);
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) std::cout << " -> ";
                std::cout << "R" << path[i];
            }
            std::cout << "\n";
        }
    }
    std::cout << std::string(60, '-') << "\n";
}
