/*
 * ============================================================
 * File:    bellman_ford.cpp
 * Project: Internet Router Network Optimization
 * Course:  COT-4400 Analysis of Algorithms — USF Bellini College
 * Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
 * ============================================================
 *
 * Description:
 *   Implements the Bellman-Ford Single-Source Shortest Path algorithm.
 *
 *   Unlike Dijkstra's algorithm, Bellman-Ford supports negative edge
 *   weights and can detect negative weight cycles in the graph.
 *
 *   Operates directly on the edge list representation of the graph,
 *   relaxing all edges V-1 times, then performing one more pass to
 *   detect negative cycles.
 *
 *   Best Case:   O(E)  — all shortest paths found in first pass
 *   Worst Case:  O(V * E) — full V-1 relaxation rounds required
 * ============================================================
 */

#include "graph.h"
#include <iostream>
#include <vector>
#include <climits>   // INT_MAX for infinity
#include <string>
#include <algorithm> // std::reverse for path reconstruction

// Symbolic constant for "no previous node" in path reconstruction
static const int BF_NO_PREDECESSOR = -1;

// ============================================================
// Path reconstruction helper
// ============================================================

/*
 * bfReconstructPath
 * Purpose:     Traces back through the prev[] array to reconstruct
 *              the shortest path from source to destination.
 * Params:      prev — predecessor array built during Bellman-Ford
 *              dest — destination router index
 * Returns:     Vector of router indices forming the path (source -> dest)
 * Time:        O(V)
 */
static std::vector<int> bfReconstructPath(const std::vector<int>& prev, int dest) {
    std::vector<int> path;
    int current = dest;

    // Walk backwards from destination to source via prev[]
    while (current != BF_NO_PREDECESSOR) {
        path.push_back(current);
        current = prev[current];
    }

    std::reverse(path.begin(), path.end());
    return path;
}

// ============================================================
// Bellman-Ford Algorithm
// ============================================================

/*
 * bellmanFord
 * Purpose:     Finds the shortest path from source to ALL other
 *              routers using edge relaxation. Also detects if a
 *              negative weight cycle exists (which would make
 *              shortest paths undefined/infinite).
 *
 *              Works with negative edge weights (unlike Dijkstra).
 *              For a graph with V vertices:
 *                - Performs V-1 full relaxation passes
 *                - Performs 1 more pass to detect negative cycles
 *
 *              Best Case:   O(E)   — paths stabilize after pass 1
 *              Worst Case:  O(V*E) — paths require all V-1 passes
 *
 * Params:      g      — the directed weighted graph of routers
 *              source — starting router index (0-indexed)
 *
 * Time Complexity:  O(V * E)
 *   — V-1 relaxation passes, each examining E edges: O(V * E)
 *
 * Space Complexity: O(V)
 *   — dist[]  — shortest distance array: O(V)
 *   — prev[]  — predecessor array: O(V)
 */
void bellmanFord(const Graph& g, int source) {
    std::cout << "\n=== Bellman-Ford Shortest Path from R" << source << " ===\n";
    std::cout << "Supports negative edge weights. Detects negative cycles.\n";
    std::cout << "Best Case Time:  O(E)     (paths stabilize in 1 pass)\n";
    std::cout << "Worst Case Time: O(V * E)\n";
    std::cout << "Space Complexity: O(V)\n\n";

    const int INFINITY_DIST = INT_MAX; // Represents unreachable routers

    // dist[v] = shortest known distance from source to router v
    std::vector<int> dist(g.numVertices, INFINITY_DIST);

    // prev[v] = predecessor of v on the shortest path from source
    std::vector<int> prev(g.numVertices, BF_NO_PREDECESSOR);

    // Initialize source router distance as 0
    dist[source] = 0;

    bool relaxedInPass = false; // Tracks early termination (Best Case)

    /*
     * RELAXATION PHASE
     * ----------------
     * Repeat V-1 times: for each directed edge (u -> v, weight w),
     * if dist[u] + w < dist[v], update dist[v] and record prev[v] = u.
     *
     * After V-1 passes, all shortest paths (without negative cycles) are found.
     * Early termination possible if no relaxation occurred in a pass (Best Case).
     */
    for (int pass = 1; pass <= g.numVertices - 1; ++pass) {
        relaxedInPass = false;

        // Examine every edge in the graph's edge list
        for (const auto& edgeTuple : g.edgeList) {
            int edgeWeight = std::get<0>(edgeTuple);
            int u          = std::get<1>(edgeTuple);
            int v          = std::get<2>(edgeTuple);

            // Only relax if source can reach u (dist[u] != INFINITY)
            if (dist[u] != INFINITY_DIST) {
                int newDist = dist[u] + edgeWeight;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    relaxedInPass = true;
                }
            }
        }

        // Best Case early termination: no relaxation means we're done
        if (!relaxedInPass) {
            std::cout << "Early termination after pass " << pass
                      << " (Best Case achieved)\n\n";
            break;
        }
    }

    /*
     * NEGATIVE CYCLE DETECTION
     * ------------------------
     * Perform one additional pass (the Vth pass).
     * If any edge can still be relaxed, a negative weight cycle exists
     * because shortest paths in a cycle-free graph stabilize within V-1 passes.
     */
    bool hasNegativeCycle = false;
    for (const auto& edgeTuple : g.edgeList) {
        int edgeWeight = std::get<0>(edgeTuple);
        int u          = std::get<1>(edgeTuple);
        int v          = std::get<2>(edgeTuple);

        if (dist[u] != INFINITY_DIST && dist[u] + edgeWeight < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle) {
        std::cout << "*** WARNING: Negative weight cycle detected! ***\n";
        std::cout << "Shortest paths are undefined (can be made arbitrarily small).\n";
        return;
    }

    // Print results: shortest distance and path for each destination router
    std::cout << "Results (Source: R" << source << "):\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << "Destination | Latency (ms) | Path\n";
    std::cout << std::string(60, '-') << "\n";

    for (int dest = 0; dest < g.numVertices; ++dest) {
        std::cout << "R" << dest << "          | ";

        if (dist[dest] == INFINITY_DIST) {
            std::cout << "UNREACHABLE   | N/A\n";
        } else {
            std::cout << dist[dest] << "ms           | ";

            // Reconstruct and print the path from source to dest
            std::vector<int> path = bfReconstructPath(prev, dest);
            for (size_t i = 0; i < path.size(); ++i) {
                if (i > 0) std::cout << " -> ";
                std::cout << "R" << path[i];
            }
            std::cout << "\n";
        }
    }
    std::cout << std::string(60, '-') << "\n";
}
