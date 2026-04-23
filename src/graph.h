/*
 * ============================================================
 * File:    graph.h
 * Project: Internet Router Network Optimization
 * Course:  COT-4400 Analysis of Algorithms — USF Bellini College
 * Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
 * ============================================================
 *
 * Description:
 *   Defines the Graph class representing a directed weighted graph.
 *   Adjacency list representation is used for BFS, DFS, Dijkstra,
 *   and Bellman-Ford. An edge list representation is also maintained
 *   for Kruskal's MST algorithm.
 *
 *   Vertices represent routers (R0–R19).
 *   Edge weights represent latency in milliseconds.
 * ============================================================
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <tuple>
#include <utility>   // std::pair
#include <iostream>
#include <string>

// ============================================================
// Graph Class
// ============================================================
class Graph {
public:
    // Number of vertices (routers)
    int numVertices;

    /*
     * Adjacency list representation.
     * adjList[u] contains pairs (v, w) meaning there is an edge
     * from u to v with weight w (latency in ms).
     */
    std::vector<std::vector<std::pair<int, int>>> adjList;

    /*
     * Edge list representation for Kruskal's algorithm.
     * Each tuple is (weight, u, v) for easy sorting by weight.
     * Note: Kruskal operates on the undirected version of the graph.
     */
    std::vector<std::tuple<int, int, int>> edgeList;

    // --------------------------------------------------------
    // Constructor
    // Purpose: Initialize the graph with n vertices and empty adjacency list.
    // Time:    O(n)
    // Space:   O(n)
    // --------------------------------------------------------
    explicit Graph(int n) : numVertices(n), adjList(n) {}

    // --------------------------------------------------------
    // addEdge
    // Purpose: Add a directed edge from u to v with weight w.
    //          Also records the edge in edgeList as (w, u, v).
    // Params:  u — source vertex index
    //          v — destination vertex index
    //          w — edge weight (latency in ms)
    // Time:    O(1) amortized
    // Space:   O(1) per call
    // --------------------------------------------------------
    void addEdge(int u, int v, int w) {
        // Add directed edge u -> v to adjacency list
        adjList[u].emplace_back(v, w);

        // Store edge in edge list as (weight, u, v) for Kruskal
        edgeList.emplace_back(w, u, v);
    }

    // --------------------------------------------------------
    // printGraph
    // Purpose: Print the adjacency list of the graph.
    //          Each router's connections and latencies are shown.
    // Time:    O(V + E)
    // Space:   O(1) auxiliary
    // --------------------------------------------------------
    void printGraph() const {
        std::cout << "\n=== Graph Adjacency List ===\n";
        std::cout << "(Format: Router -> Neighbor [weight ms])\n\n";

        for (int u = 0; u < numVertices; ++u) {
            std::cout << "R" << u << " -> ";
            if (adjList[u].empty()) {
                std::cout << "(no outgoing edges)";
            } else {
                for (size_t i = 0; i < adjList[u].size(); ++i) {
                    int neighbor = adjList[u][i].first;
                    int weight   = adjList[u][i].second;
                    std::cout << "R" << neighbor << "[" << weight << "ms]";
                    if (i + 1 < adjList[u].size()) {
                        std::cout << ", ";
                    }
                }
            }
            std::cout << "\n";
        }
        std::cout << "\nTotal Routers (Vertices): " << numVertices << "\n";
        std::cout << "Total Connections (Edges): " << edgeList.size() << "\n";
    }
};

#endif // GRAPH_H
