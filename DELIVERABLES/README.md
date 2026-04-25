# COT-4400 Router Network Optimization — Final Submission

**Course:** Analysis of Algorithms  
**Institution:** USF Bellini College of AI, Cybersecurity & Computing  
**Team:** Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)  
**Date:** April 25, 2026

---

## 📋 Deliverables Package Contents

This folder contains all materials required for final submission:

### 📊 Presentation Materials
- **COT4400_Presentation.pptx** — Final presentation slides (15 slides)
- **presentation_script.md** — Complete speaker notes and talking points

### 📄 Written Report
- **COT4400_Report.pdf** — Final written report (PDF format)
- **COT4400_Report.docx** — Final written report (Word format)

### 💻 Source Code
- **src/** — All C++ source files
  - `graph.h` — Graph class definition (adjacency list + edge list)
  - `main.cpp` — Entry point, constructs 20-router network
  - `bfs_dfs.cpp` — Breadth-First & Depth-First Search implementations
  - `dijkstra.cpp` — Dijkstra's shortest path algorithm
  - `bellman_ford.cpp` — Bellman-Ford shortest path algorithm
  - `kruskal.cpp` — Kruskal's Minimum Spanning Tree with Union-Find
  - `experimental.cpp` — Performance benchmarking suite

### 📈 Results & Analysis
- **results/experimental_results.md** — Timing results across 4 graph scenarios
- **output.html** — Styled browser-friendly view of all program output
- **docs/complexity_analysis.md** — Detailed Big-O breakdown for all algorithms

### 🛠️ Build System
- **Makefile** — Compilation and execution automation

---

## 🚀 How to Use This Package

### Compile the Project
```bash
cd DELIVERABLES
make
```

### Run the Program
```bash
./router_network
```

Or compile and run in one command:
```bash
make run
```

### Clean Build Artifacts
```bash
make clean
```

---

## 📊 Project Summary

**Network Model:**
- 20 routers (vertices R0–R19)
- 33 directed weighted edges (latency in milliseconds)
- Layered architecture: Core → Distribution → Edge → Access

**Algorithms Implemented:**
1. **BFS** — Graph traversal, O(V+E)
2. **DFS** — Graph traversal, O(V+E)
3. **Dijkstra** — Shortest path (non-negative weights), O((V+E) log V)
4. **Bellman-Ford** — Shortest path (supports negative weights), O(V×E)
5. **Kruskal** — Minimum Spanning Tree, O(E log E)

**Key Results:**
- **Shortest path (R0→R19):** 49ms via R0→R1→R4→R9→R15→R19
- **MST Total Weight:** 171ms across 19 edges
- **Performance:** BFS/DFS < 1μs on all graphs; Dijkstra 210μs on large dense graphs

---

## 📋 System Requirements

- **Compiler:** g++ with C++17 support
- **Build Tool:** GNU Make
- **Platform:** Linux, macOS, or Windows (WSL/Cygwin)

**Compilation Flags:**
```
g++ -std=c++17 -O2 -Wall -Wextra
```

---

## 📝 Documentation Links

| Document | File |
|----------|------|
| Presentation | `COT4400_Presentation.pptx` |
| Written Report | `COT4400_Report.pdf` |
| Complexity Analysis | `docs/complexity_analysis.md` |
| Experimental Results | `results/experimental_results.md` |
| Program Output (Styled) | `output.html` |

---

## ✅ Submission Checklist

- ✓ Presentation slides (.pptx)
- ✓ Written report (.pdf + .docx)
- ✓ Complete source code (.cpp/.h files)
- ✓ Program output results
- ✓ Experimental performance analysis
- ✓ Build system (Makefile)
- ✓ Complexity analysis documentation
- ✓ This README

---

**Status:** Ready for submission  
**Last Updated:** April 25, 2026
