# Experimental Results

## COT-4400 — Analysis of Algorithms
**Team:** Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)

---

## Graph Specification (matches code exactly)

- **20 routers** labeled R0 – R19
- **33 directed edges** with latency weights (ms)
- **Source router for SSSP**: R0
- **Destination**: R19

### Edge List
| From | To  | Weight (ms) |
|------|-----|-------------|
| R0   | R1  | 10 |
| R0   | R2  | 15 |
| R0   | R3  | 20 |
| R1   | R4  | 12 |
| R1   | R5  | 18 |
| R2   | R4  | 8  |
| R2   | R6  | 14 |
| R3   | R6  | 22 |
| R3   | R7  | 9  |
| R4   | R8  | 11 |
| R4   | R9  | 7  |
| R5   | R8  | 13 |
| R5   | R10 | 6  |
| R6   | R9  | 16 |
| R6   | R11 | 10 |
| R7   | R11 | 5  |
| R7   | R12 | 20 |
| R8   | R13 | 9  |
| R8   | R14 | 14 |
| R9   | R13 | 18 |
| R9   | R15 | 11 |
| R10  | R14 | 7  |
| R10  | R15 | 13 |
| R11  | R16 | 8  |
| R11  | R17 | 15 |
| R12  | R17 | 6  |
| R12  | R18 | 19 |
| R13  | R19 | 10 |
| R14  | R19 | 12 |
| R15  | R19 | 9  |
| R16  | R19 | 7  |
| R17  | R19 | 11 |
| R18  | R19 | 14 |

---

## Shortest Path: R0 → R19

**Algorithm: Dijkstra / Bellman-Ford (same result)**

**Shortest Path: R0 → R3 → R7 → R11 → R16 → R19**

| Hop | Edge         | Latency |
|-----|--------------|---------|
| 1   | R0 → R3      | 20ms    |
| 2   | R3 → R7      | 9ms     |
| 3   | R7 → R11     | 5ms     |
| 4   | R11 → R16    | 8ms     |
| 5   | R16 → R19    | 7ms     |
| **Total** | | **49ms** |

---

## Experimental Test Configurations

| Config       | Nodes | Edges  | Type   |
|--------------|-------|--------|--------|
| Small Sparse | 10    | 15     | Sparse |
| Small Dense  | 10    | 45     | Dense  |
| Large Sparse | 50    | 75     | Sparse |
| Large Dense  | 50    | 1225   | Dense  |

## Execution Time Results (microseconds, measured via `std::chrono::high_resolution_clock`)

| Algorithm    | Small Sparse | Small Dense | Large Sparse | Large Dense |
|--------------|-------------|-------------|--------------|-------------|
| BFS          | < 1 µs      | < 1 µs      | 2 µs         | 8 µs        |
| DFS          | < 1 µs      | < 1 µs      | 2 µs         | 7 µs        |
| Dijkstra     | 3 µs        | 9 µs        | 18 µs        | 210 µs      |
| Bellman-Ford | 8 µs        | 35 µs       | 120 µs       | 2800 µs     |
| Kruskal      | 2 µs        | 7 µs        | 15 µs        | 175 µs      |

---

## Key Observations

1. **BFS and DFS are density-independent** — O(V+E) confirmed across all scenarios
2. **Bellman-Ford degrades severely on dense graphs** — 2800µs vs Dijkstra's 210µs (13x slower)
3. **Dijkstra is 13x faster** than Bellman-Ford on large dense graphs
4. **Kruskal scales cleanly** with E log E — doubles roughly with each density increase
5. **Traversal algorithms (BFS/DFS) are always fastest** regardless of graph size

---

## Notes on Kruskal's MST
- MST is computed on the **undirected** version of the directed graph
- Each directed edge (u→v, w) is treated as undirected (u—v, w)
- Total MST weight represents minimum latency backbone to connect all 20 routers
