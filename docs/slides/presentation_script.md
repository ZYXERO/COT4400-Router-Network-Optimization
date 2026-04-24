# COT-4400 — Router Network Optimization
## Full Presentation Script

**Course:** COT-4400 Analysis of Algorithms — USF Bellini College  
**Team:** Kaushik Selvakumar (U75300364) | Seyoung Kan U (U36444259)

> Speaker notes are also embedded in `COT4400_Presentation.pptx` under each slide.

---

## Slide 1 — Title

**🎤 Kaushik:**

Hey everyone, we're presenting our project on router network optimization using graph algorithms.
I'm Kaushik, and this is Seyoung.
We modeled a real-world internet routing problem and analyzed different algorithms for it.

---

## Slide 2 — Problem Overview

**🎤 Seyoung:**

So the main idea is that the internet is basically a network of routers constantly passing data.
Each router needs to decide the best next hop to minimize delay.

This naturally becomes a shortest path problem on a graph.

And this is exactly what real protocols like OSPF and BGP are solving.

---

## Slide 3 — Graph Model

**🎤 Seyoung:**

We model the network as a directed weighted graph.

We have:
- 20 routers as vertices
- 33 directed edges
- weights represent latency in milliseconds

So overall, it's a directed, weighted graph with no negative weights.

---

## Slide 4 — Architecture Layers

**🎤 Seyoung:**

We also structured the network into layers to reflect real systems.

- **Core** handles backbone routing
- **Distribution** aggregates traffic
- **Edge** connects to external networks
- **Access** connects to end users

This makes the model more realistic instead of just a random graph.

---

## Slide 5 — Dataset

**🎤 Seyoung:**

Here are some key edges from our dataset.

These represent actual latency values between routers.

And on the right, we show how routers are grouped into layers.

The full structure is shown in the adjacency list output next.

---

## Slide 6 — Adjacency Output

**🎤 Seyoung:**

This is the actual graph printed from our program.

It confirms that we correctly built all 20 routers and 33 edges.

---

## Slide 7 — BFS

**🎤 Kaushik:**

For traversal, we first used BFS.

It explores the graph level by level using a queue.

It's useful for checking reachability and finding shortest paths in terms of hops.

Time complexity is O(V + E), so it's very efficient.

---

## Slide 8 — DFS

**🎤 Kaushik:**

DFS goes deep into the graph first using recursion.

It's useful for exploring structure and detecting cycles.

It has the same time complexity as BFS — O(V + E) — but behaves differently.

---

## Slide 9 — Dijkstra

**🎤 Kaushik:**

This is the main algorithm for shortest path.

Dijkstra uses a priority queue and always expands the node with the smallest distance.

Time complexity is O((V + E) log V).

From our output, the shortest path from R0 to R19 is:

> **R0 → R1 → R4 → R9 → R15 → R19 = 49 ms**

This is the minimum latency path found by the algorithm.

---

## Slide 10 — Bellman-Ford

**🎤 Kaushik:**

Bellman-Ford is similar to Dijkstra but more flexible.

It supports negative weights and can detect negative cycles.

However, it's slower with O(V × E) time complexity.

In our case, both algorithms produced the same shortest path, confirming correctness.

---

## Slide 11 — Kruskal

**🎤 Kaushik:**

Kruskal is used for building a minimum spanning tree.

Instead of shortest path, it minimizes total network cost.

From our output:
- **19 edges**
- **Total weight = 171 ms**

We apply it on an undirected version of the graph.

---

## Slide 12 — Complexity Summary

**🎤 Kaushik:**

This slide summarizes the complexity of all algorithms.

| Algorithm    | Time Complexity  |
|--------------|-----------------|
| BFS          | O(V + E)        |
| DFS          | O(V + E)        |
| Dijkstra     | O((V+E) log V)  |
| Bellman-Ford | O(V × E)        |
| Kruskal      | O(E log E)      |

BFS and DFS are linear, Dijkstra is logarithmic due to the heap, Bellman-Ford is slower, and Kruskal depends on sorting edges.

---

## Slide 13 — Experimental Results

**🎤 Kaushik:**

We tested all algorithms on different graph sizes.

Key observations:
- BFS and DFS are the fastest
- Dijkstra and Bellman-Ford perform similarly at this scale
- Kruskal increases significantly on dense graphs due to sorting overhead

---

## Slide 14 — Conclusion

**🎤 Kaushik:**

So overall:

- **Dijkstra** is best for shortest path with non-negative weights
- **Bellman-Ford** is useful when negative weights exist
- **BFS and DFS** are great for graph exploration
- **Kruskal** is useful for network design

This shows how these algorithms directly apply to real-world internet routing.

---

## Slide 15 — Thank You

**🎤 Kaushik:**

And that's our project — thank you for your time.
We're happy to take any questions.

---

*Script also embedded as speaker notes in `COT4400_Presentation.pptx`.*
