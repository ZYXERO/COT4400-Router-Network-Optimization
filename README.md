# Internet Router Network Optimization
## COT-4400 — Analysis of Algorithms
### USF Bellini College of Artificial Intelligence, Cybersecurity and Computing

**Team Members:**
- Seyoung Kan U — U36444259
- Kaushik Selvakumar — U75300364

## Project Description
This project models the internet as a directed weighted graph where:
- **Vertices** = Routers (R0 to R19)
- **Edges** = Directed connections with latency weights (ms)
- **Goal** = Find the most efficient path for data packets

## Algorithms Implemented
| Algorithm | Type | Time Complexity |
|---|---|---|
| BFS | Traversal | O(V + E) |
| DFS | Traversal | O(V + E) |
| Dijkstra | Shortest Path | O((V + E) log V) |
| Bellman-Ford | Shortest Path | O(V * E) |
| Kruskal | MST | O(E log E) |

## File Structure
```
router_network/
├── graph.h
├── bfs_dfs.cpp
├── dijkstra.cpp
├── bellman_ford.cpp
├── kruskal.cpp
├── experimental.cpp
├── main.cpp
├── Makefile
└── README.md
```

## How to Compile and Run
```bash
make
./router_network
```

## Course
COT-4400 Analysis of Algorithms — Final Project
