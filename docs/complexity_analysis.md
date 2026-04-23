# Complexity Analysis

## COT-4400 — Analysis of Algorithms
**Team:** Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)

---

## BFS — Breadth-First Search

| Case | Time | Space |
|------|------|-------|
| Best | O(1) | O(V) |
| Average | O(V + E) | O(V) |
| Worst | O(V + E) | O(V) |

**Explanation:** Each vertex is enqueued and dequeued once. Each edge is
examined once. Queue holds at most O(V) elements.

---

## DFS — Depth-First Search

| Case | Time | Space |
|------|------|-------|
| Best | O(1) | O(V) |
| Average | O(V + E) | O(V) |
| Worst | O(V + E) | O(V) |

**Explanation:** Each vertex is visited once via recursion. The call stack
depth is at most O(V) in the worst case (linear chain graph).

---

## Dijkstra's Algorithm

| Case | Time | Space |
|------|------|-------|
| Best | O(V log V) | O(V) |
| Average | O((V + E) log V) | O(V) |
| Worst | O((V + E) log V) | O(V) |

**Explanation:** Each vertex is extracted from the min-heap once O(V log V).
Each edge relaxation may trigger a heap insertion O(E log V).
Does NOT support negative edge weights.

---

## Bellman-Ford Algorithm

| Case | Time | Space |
|------|------|-------|
| Best | O(E) | O(V) |
| Average | O(V × E) | O(V) |
| Worst | O(V × E) | O(V) |

**Explanation:** Performs V-1 passes over all E edges. Best case occurs when
all shortest paths are found in the first relaxation pass.
Supports negative weights. Detects negative cycles on the Vth pass.

---

## Kruskal's Algorithm (MST)

| Case | Time | Space |
|------|------|-------|
| Best | O(E log E) | O(V) |
| Average | O(E log E) | O(V) |
| Worst | O(E log E) | O(V) |

**Explanation:** Dominated by sorting all edges O(E log E). Union-Find
with path compression and union by rank runs in near O(1) per operation.
Applied to undirected version of the graph.

---

## Summary Comparison

| Algorithm | Time Complexity | Space | Handles Neg. Weights |
|-----------|----------------|-------|----------------------|
| BFS | O(V + E) | O(V) | N/A (unweighted) |
| DFS | O(V + E) | O(V) | N/A (unweighted) |
| Dijkstra | O((V+E) log V) | O(V) | No |
| Bellman-Ford | O(V × E) | O(V) | Yes |
| Kruskal | O(E log E) | O(V) | N/A (MST) |
