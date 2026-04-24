# Internet Router Network Optimization
## COT-4400: Analysis of Algorithms — Final Project
### USF Bellini College of Artificial Intelligence, Cybersecurity and Computing

**Team Members:**
- Kaushik Selvakumar — U75300364
- Seyoung Kan U — U36444259

---

## Project Description

This project models the internet as a **directed weighted graph** where routers are vertices and directed connections carry latency weights in milliseconds. We implement and compare five core graph algorithms to solve the shortest path and minimum spanning tree problems in the context of real-world network routing.

---

## Repository Structure

```
COT4400-Router-Network-Optimization/
├── src/                             # All C++ source files
│   ├── graph.h                      # Graph class (adjacency list + edge list)
│   ├── bfs_dfs.cpp                  # BFS and DFS traversal
│   ├── dijkstra.cpp                 # Dijkstra's shortest path
│   ├── bellman_ford.cpp             # Bellman-Ford shortest path
│   ├── kruskal.cpp                  # Kruskal's MST (Union-Find)
│   ├── experimental.cpp             # Performance benchmarking suite
│   └── main.cpp                     # Entry point — builds graph, runs all sections
├── docs/
│   ├── report/
│   │   ├── COT4400_Report.docx      # Final written report (Word)
│   │   └── COT4400_Report.pdf       # Final written report (PDF)
│   ├── slides/
│   │   ├── COT4400_Presentation.pptx    # Final presentation slides
│   │   └── presentation_script.md       # Full speaker script (15 slides)
│   └── complexity_analysis.md       # Detailed Big-O breakdown for all algorithms
├── results/
│   └── experimental_results.md      # Timing results across 4 graph scenarios
├── output.html                      # Styled browser view of all 7 program output sections
├── Makefile
└── README.md
```

---

## Algorithms Implemented

| Algorithm    | Type          | Time Complexity  | Space | Handles Neg. Weights |
|--------------|---------------|-----------------|-------|----------------------|
| BFS          | Traversal     | O(V + E)        | O(V)  | N/A                  |
| DFS          | Traversal     | O(V + E)        | O(V)  | N/A                  |
| Dijkstra     | Shortest Path | O((V+E) log V)  | O(V)  | ❌ No                |
| Bellman-Ford | Shortest Path | O(V × E)        | O(V)  | ✅ Yes               |
| Kruskal      | MST           | O(E log E)      | O(V)  | N/A                  |

---

## Graph Specification

- **20 routers** labeled R0 – R19 (vertices)
- **33 directed edges** with latency weights in milliseconds
- **Source**: R0 | **Destination**: R19
- **Shortest path**: R0 → R1 → R4 → R9 → R15 → R19 = **49ms**
- **MST total weight**: **171ms** across 19 edges
- Network topology reflects a layered architecture: Core → Distribution → Edge → Access

---

## How to Compile and Run

```bash
# Compile all source files
make

# Run the program (all 7 sections)
./router_network

# Compile and run in one step
make run

# Clean build artifacts
make clean
```

**Requirements:** g++ with C++17 support (`g++ -std=c++17 -O2`)

---

## Program Output Sections

| Section | Content |
|---------|---------|
| Section 1 | Graph Adjacency List (20 routers, 33 edges) |
| Section 2 | BFS Traversal from R0 |
| Section 3 | DFS Traversal from R0 |
| Section 4 | Dijkstra's Shortest Path (all destinations) |
| Section 5 | Bellman-Ford Shortest Path (early termination pass 2) |
| Section 6 | Kruskal's MST (19 edges, 171ms total) |
| Section 7 | Experimental Performance Analysis (4 graph scenarios) |

> View styled output: [output.html](./output.html)

---

## Documentation

| Document | Location |
|----------|----------|
| Written Report (Word) | `docs/report/COT4400_Report.docx` |
| Written Report (PDF) | `docs/report/COT4400_Report.pdf` |
| Presentation Slides | `docs/slides/COT4400_Presentation.pptx` |
| Presentation Script | `docs/slides/presentation_script.md` |
| Complexity Analysis | `docs/complexity_analysis.md` |
| Experimental Results | `results/experimental_results.md` |

---

## Course

**COT-4400: Analysis of Algorithms** — Final Project  
USF Bellini College of AI, Cybersecurity & Computing
