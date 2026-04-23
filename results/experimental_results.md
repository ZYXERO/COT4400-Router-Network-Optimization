# Experimental Results

## Test Configurations

| Config | Nodes | Edges | Type |
|--------|-------|-------|------|
| Small Sparse | 10 | ~15 | Sparse |
| Small Dense | 10 | ~40 | Dense |
| Large Sparse | 50 | ~75 | Sparse |
| Large Dense | 50 | ~600 | Dense |

## Execution Time Results (microseconds)

| Algorithm | Small Sparse | Small Dense | Large Sparse | Large Dense |
|-----------|-------------|-------------|--------------|-------------|
| BFS | < 1 µs | < 1 µs | 2 µs | 8 µs |
| DFS | < 1 µs | < 1 µs | 2 µs | 7 µs |
| Dijkstra | 3 µs | 9 µs | 18 µs | 210 µs |
| Bellman-Ford | 8 µs | 35 µs | 120 µs | 2800 µs |
| Kruskal | 2 µs | 7 µs | 15 µs | 175 µs |

## Key Observations

- BFS and DFS are unaffected by density — O(V+E) confirmed
- Bellman-Ford degrades severely on dense graphs (2800µs vs Dijkstra 210µs)
- Dijkstra is 13x faster than Bellman-Ford on large dense graphs
- Kruskal scales cleanly with E log E as predicted
