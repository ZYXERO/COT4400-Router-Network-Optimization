/*
 * ============================================================
 * File:    main.cpp
 * Project: Internet Router Network Optimization
 * Course:  COT-4400 Analysis of Algorithms — USF Bellini College
 * Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
 * ============================================================
 *
 * Description:
 *   Entry point for the Router Network Optimization project.
 *   Builds a directed weighted graph of 20 routers (R0–R19),
 *   where edges represent network connections and weights
 *   represent latency in milliseconds.
 *
 *   Executes and displays results for:
 *     1. Graph visualization (adjacency list)
 *     2. BFS traversal from R0
 *     3. DFS traversal from R0
 *     4. Dijkstra's Shortest Path from R0
 *     5. Bellman-Ford Shortest Path from R0
 *     6. Kruskal's Minimum Spanning Tree
 *     7. Experimental performance analysis
 * ============================================================
 */

#include "graph.h"
#include <iostream>
#include <string>

// ============================================================
// Forward Declarations
// ============================================================
// Functions are defined in their respective .cpp files.
// They all accept a Graph reference as their primary argument.

void BFS(const Graph& g, int source);
void DFS(const Graph& g, int source);
void dijkstra(const Graph& g, int source);
void bellmanFord(const Graph& g, int source);
void kruskal(Graph& g);
void runExperiments();

// ============================================================
// Section Separator Helper
// ============================================================

/*
 * printSeparator
 * Purpose:     Prints a visual divider with a section title
 *              to improve readability of program output.
 * Params:      title — label for the section being started
 */
static void printSeparator(const std::string& title) {
    const std::string LINE(70, '=');
    std::cout << "\n" << LINE << "\n";
    std::cout << "  " << title << "\n";
    std::cout << LINE << "\n";
}

// ============================================================
// Main Function
// ============================================================

/*
 * main
 * Purpose:     Entry point. Constructs the 20-router network graph
 *              and runs all algorithms sequentially with clear output.
 *
 * Graph:       20 vertices (R0–R19), directed, weighted (latency in ms)
 * Source:      R0 for all single-source algorithms
 */
int main() {
    // --------------------------------------------------------
    // Project Header
    // --------------------------------------------------------
    std::cout << "======================================================\n";
    std::cout << "   Internet Router Network Optimization\n";
    std::cout << "   COT-4400 Analysis of Algorithms\n";
    std::cout << "   USF Bellini College of AI, Cybersecurity & Computing\n";
    std::cout << "   Team: Seyoung Kan U (U36444259)\n";
    std::cout << "         Kaushik Selvakumar (U75300364)\n";
    std::cout << "======================================================\n";

    // --------------------------------------------------------
    // Graph Construction
    // Build the 20-router directed weighted graph.
    // Vertices: R0–R19 (routers)
    // Edges: directed connections with latency weights in ms
    // --------------------------------------------------------
    const int NUM_ROUTERS = 20; // Total number of routers in the network
    Graph g(NUM_ROUTERS);

    // --- R0's outgoing connections ---
    g.addEdge(0,  1,  10);  // R0 -> R1 : 10ms
    g.addEdge(0,  2,  15);  // R0 -> R2 : 15ms
    g.addEdge(0,  3,  20);  // R0 -> R3 : 20ms

    // --- R1's outgoing connections ---
    g.addEdge(1,  4,  12);  // R1 -> R4 : 12ms
    g.addEdge(1,  5,  18);  // R1 -> R5 : 18ms

    // --- R2's outgoing connections ---
    g.addEdge(2,  4,   8);  // R2 -> R4 :  8ms
    g.addEdge(2,  6,  14);  // R2 -> R6 : 14ms

    // --- R3's outgoing connections ---
    g.addEdge(3,  6,  22);  // R3 -> R6 : 22ms
    g.addEdge(3,  7,   9);  // R3 -> R7 :  9ms

    // --- R4's outgoing connections ---
    g.addEdge(4,  8,  11);  // R4 -> R8 : 11ms
    g.addEdge(4,  9,   7);  // R4 -> R9 :  7ms

    // --- R5's outgoing connections ---
    g.addEdge(5,  8,  13);  // R5 -> R8 : 13ms
    g.addEdge(5, 10,   6);  // R5 -> R10:  6ms

    // --- R6's outgoing connections ---
    g.addEdge(6,  9,  16);  // R6 -> R9 : 16ms
    g.addEdge(6, 11,  10);  // R6 -> R11: 10ms

    // --- R7's outgoing connections ---
    g.addEdge(7, 11,   5);  // R7 -> R11:  5ms
    g.addEdge(7, 12,  20);  // R7 -> R12: 20ms

    // --- R8's outgoing connections ---
    g.addEdge(8, 13,   9);  // R8 -> R13:  9ms
    g.addEdge(8, 14,  14);  // R8 -> R14: 14ms

    // --- R9's outgoing connections ---
    g.addEdge(9, 13,  18);  // R9 -> R13: 18ms
    g.addEdge(9, 15,  11);  // R9 -> R15: 11ms

    // --- R10's outgoing connections ---
    g.addEdge(10, 14,  7);  // R10 -> R14:  7ms
    g.addEdge(10, 15, 13);  // R10 -> R15: 13ms

    // --- R11's outgoing connections ---
    g.addEdge(11, 16,  8);  // R11 -> R16:  8ms
    g.addEdge(11, 17, 15);  // R11 -> R17: 15ms

    // --- R12's outgoing connections ---
    g.addEdge(12, 17,  6);  // R12 -> R17:  6ms
    g.addEdge(12, 18, 19);  // R12 -> R18: 19ms

    // --- R13's outgoing connections ---
    g.addEdge(13, 19, 10);  // R13 -> R19: 10ms

    // --- R14's outgoing connections ---
    g.addEdge(14, 19, 12);  // R14 -> R19: 12ms

    // --- R15's outgoing connections ---
    g.addEdge(15, 19,  9);  // R15 -> R19:  9ms

    // --- R16's outgoing connections ---
    g.addEdge(16, 19,  7);  // R16 -> R19:  7ms

    // --- R17's outgoing connections ---
    g.addEdge(17, 19, 11);  // R17 -> R19: 11ms

    // --- R18's outgoing connections ---
    g.addEdge(18, 19, 14);  // R18 -> R19: 14ms

    // --------------------------------------------------------
    // Section 1: Graph Visualization
    // --------------------------------------------------------
    printSeparator("SECTION 1: Graph Adjacency List");
    g.printGraph();

    // --------------------------------------------------------
    // Section 2: BFS Traversal
    // --------------------------------------------------------
    printSeparator("SECTION 2: Breadth-First Search (BFS)");
    BFS(g, 0); // Source: R0

    // --------------------------------------------------------
    // Section 3: DFS Traversal
    // --------------------------------------------------------
    printSeparator("SECTION 3: Depth-First Search (DFS)");
    DFS(g, 0); // Source: R0

    // --------------------------------------------------------
    // Section 4: Dijkstra's Shortest Path
    // --------------------------------------------------------
    printSeparator("SECTION 4: Dijkstra's Shortest Path Algorithm");
    dijkstra(g, 0); // Source: R0

    // --------------------------------------------------------
    // Section 5: Bellman-Ford Shortest Path
    // --------------------------------------------------------
    printSeparator("SECTION 5: Bellman-Ford Shortest Path Algorithm");
    bellmanFord(g, 0); // Source: R0

    // --------------------------------------------------------
    // Section 6: Kruskal's MST
    // --------------------------------------------------------
    printSeparator("SECTION 6: Kruskal's Minimum Spanning Tree");
    kruskal(g);

    // --------------------------------------------------------
    // Section 7: Experimental Performance Analysis
    // --------------------------------------------------------
    printSeparator("SECTION 7: Experimental Performance Analysis");
    runExperiments();

    // --------------------------------------------------------
    // Program Footer
    // --------------------------------------------------------
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "  All algorithms completed successfully.\n";
    std::cout << "  COT-4400 Final Project — Router Network Optimization\n";
    std::cout << std::string(70, '=') << "\n\n";

    return 0;
}
