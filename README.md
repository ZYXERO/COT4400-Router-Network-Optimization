# Internet Router Network Optimization
## COT-4400 — Analysis of Algorithms
### USF Bellini College of Artificial Intelligence, Cybersecurity and Computing

**Team Members:**
- Seyoung Kan — U36444259
- Kaushik Selvakumar — U75300364

---

## Project Description
This project models the internet as a directed weighted graph where:
- **Vertices** = Routers (R0 to R19)
- **Edges** = Directed connections with latency weights (ms)
- **Goal** = Find the most efficient path for data packets using graph algorithms

---

## Repository Structure
```
COT4400-Router-Network-Optimization/
├── src/                        # All C++ source files
│   ├── graph.h                 # Graph class definition
│   ├── bfs_dfs.cpp             # BFS and DFS traversal
│   ├── dijkstra.cpp            # Dijkstra shortest path
│   ├── bellman_ford.cpp        # Bellman-Ford shortest path
│   ├── kruskal.cpp             # Kruskal MST
│   ├── experimental.cpp        # Performance experiments
│   └── main.cpp                # Entry point
├── docs/
│   ├── report/                 # Final written report (.docx)
│   ├── slides/                 # Presentation slides (.pptx)
│   └── complexity_analysis.md  # Full complexity breakdown
├── results/
│   └── experimental_results.md # Timing results and observations
├── Makefile
└── README.md
```

---

## Algorithms Implemented

| Algorithm | Type | Time Complexity | Handles Neg. Weights |
|-----------|------|----------------|----------------------|
| BFS | Traversal | O(V + E) | N/A |
| DFS | Traversal | O(V + E) | N/A |
| Dijkstra | Shortest Path | O((V + E) log V) | No |
| Bellman-Ford | Shortest Path | O(V × E) | Yes |
| Kruskal | MST | O(E log E) | N/A |

---

## How to Compile and Run

```bash
# Compile
make

# Run
./router_network

# Compile and run in one step
make run

# Clean build
make clean
```

---

## Graph Specification

- **20 routers** labeled R0 – R19
- **Directed weighted edges** (latency in ms)
- **Source router**: R0
- **Destination**: R19
- Topology mimics a real internet backbone: Core → Edge → Distribution → Access → Gateway

---

## Documentation

| Document | Location |
|----------|----------|
| Written Report | `docs/report/COT4400_Final_Report.docx` |
| Presentation | `docs/slides/COT4400_Presentation.pptx` |
| Complexity Analysis | `docs/complexity_analysis.md` |
| Experimental Results | `results/experimental_results.md` |

---

## Course
COT-4400 Analysis of Algorithms — Final Project
