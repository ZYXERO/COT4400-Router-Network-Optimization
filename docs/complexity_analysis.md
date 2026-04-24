# Complexity Analysis

## COT-4400 — Analysis of Algorithms
**Team:** Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)

---

## Graph Specification

- **20 routers** labeled R0 – R19 (vertices)
- **33 directed edges** with latency weights in milliseconds
- Directed weighted graph — edges are one-way
- MST (Kruskal) treats edges as undirected

---

## BFS — Breadth-First Search

| Case    | Time      | Space |
|---------|-----------|-------|
| Best    | O(1)      | O(V)  |
| Average | O(V + E)  | O(V)  |
| Worst   | O(V + E)  | O(V)  |

**Explanation:** Each vertex is enqueued and dequeued exactly once. Each edge is
examined once. Queue holds at most O(V) elements at any time.

---

## DFS — Depth-First Search

| Case    | Time      | Space |
|---------|-----------|-------|
| Best    | O(1)      | O(V)  |
| Average | O(V + E)  | O(V)  |
| Worst   | O(V + E)  | O(V)  |

**Explanation:** Each vertex is visited exactly once via recursion. The call stack
depth is at most O(V) in the worst case (linear chain graph).

---

## Dijkstra's Algorithm

| Case    | Time               | Space |
|---------|--------------------|-------|
| Best    | O(V log V)         | O(V)  |
| Average | O((V + E) log V)   | O(V)  |
| Worst   | O((V + E) log V)   | O(V)  |

**Explanation:** Each vertex is extracted from the min-heap once — O(V log V).
Each edge relaxation may trigger a heap insertion — O(E log V).
**Does NOT support negative edge weights.**
All 33 edge weights in this network are positive (latency ≥ 1ms), so Dijkstra is valid.

---

## Bellman-Ford Algorithm

| Case    | Time       | Space |
|---------|------------|-------|
| Best    | O(E)       | O(V)  |
| Average | O(V × E)   | O(V)  |
| Worst   | O(V × E)   | O(V)  |

**Explanation:** Performs V-1 passes over all E edges (33 edges, 20 vertices).
Best case occurs when all shortest paths stabilize in the first relaxation pass.
Supports negative weights. Detects negative cycles on the Vth pass.

---

## Kruskal's Algorithm (MST)

| Case    | Time        | Space |
|---------|-------------|-------|
| Best    | O(E log E)  | O(V)  |
| Average | O(E log E)  | O(V)  |
| Worst   | O(E log E)  | O(V)  |

**Explanation:** Dominated by sorting all 33 edges — O(E log E).
Union-Find with path compression and union by rank runs in O(α(V)) ≈ O(1) per operation.
**Applied to the undirected version of the graph** — each directed edge (u→v, w)
is treated as undirected link (u—v, w) for MST construction.

---

## Summary Comparison

| Algorithm    | Time Complexity  | Space | Handles Neg. Weights | Applied To         |
|--------------|-----------------|-------|----------------------|--------------------|
| BFS          | O(V + E)        | O(V)  | N/A (unweighted)     | Directed graph     |
| DFS          | O(V + E)        | O(V)  | N/A (unweighted)     | Directed graph     |
| Dijkstra     | O((V+E) log V)  | O(V)  | ❌ No                | Directed graph     |
| Bellman-Ford | O(V × E)        | O(V)  | ✅ Yes               | Directed graph     |
| Kruskal      | O(E log E)      | O(V)  | N/A (MST)            | Undirected version |

---

## Verified Shortest Path: R0 → R19

**Path: R0 → R3 → R7 → R11 → R16 → R19**
**Total latency: 20 + 9 + 5 + 8 + 7 = 49ms**

This is confirmed by both Dijkstra and Bellman-Ford on the 20-node 33-edge graph.
