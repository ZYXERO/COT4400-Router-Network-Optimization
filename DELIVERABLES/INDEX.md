# DELIVERABLES — Complete Submission Package
**Internet Router Network Optimization — COT-4400 Final Project**

---

## 📦 Package Overview

This `DELIVERABLES/` folder contains **all materials** needed for your final course submission:

### ✅ What's Included

```
DELIVERABLES/
├── README.md                           (this file)
├── SUBMISSION_MANIFEST.txt             (file inventory)
│
├── 📊 PRESENTATION/
│   ├── COT4400_Presentation.pptx       (15 slides - presentation ready)
│   └── presentation_script.md          (full speaker notes)
│
├── 📄 REPORT/
│   ├── COT4400_Report.pdf              (PDF version)
│   └── COT4400_Report.docx             (Word version)
│
├── 💻 SOURCE_CODE/
│   ├── graph.h                         (graph class definition)
│   ├── main.cpp                        (entry point)
│   ├── bfs_dfs.cpp                     (traversal algorithms)
│   ├── dijkstra.cpp                    (shortest path)
│   ├── bellman_ford.cpp                (shortest path with negatives)
│   ├── kruskal.cpp                     (MST algorithm)
│   ├── experimental.cpp                (performance benchmarks)
│   └── Makefile                        (build system)
│
├── 📈 RESULTS/
│   ├── output.html                     (styled program output)
│   ├── experimental_results.md         (performance data)
│   └── complexity_analysis.md          (Big-O analysis)
│
└── 📋 DOCUMENTATION/
    ├── SUBMISSION_INSTRUCTIONS.md      (how to prepare submission)
    └── PROJECT_SUMMARY.txt             (quick reference)
```

---

## 🚀 Quick Start

### 1️⃣ Compile
```bash
cd DELIVERABLES
make
```

### 2️⃣ Run
```bash
./router_network
```

### 3️⃣ View Results
- **Console output:** Direct program output with all 7 sections
- **Formatted view:** Open `results/output.html` in a browser

---

## 📋 Files Mapping

### Presentation Materials
| File | Type | Purpose |
|------|------|---------|
| `COT4400_Presentation.pptx` | PowerPoint | Presentation slides (15 slides) |
| `presentation_script.md` | Markdown | Full speaker script |

### Documentation
| File | Type | Purpose |
|------|------|---------|
| `COT4400_Report.pdf` | PDF | Final written report |
| `COT4400_Report.docx` | Word | Final written report (editable) |
| `complexity_analysis.md` | Markdown | Detailed complexity analysis |

### Code & Build
| File | Type | Purpose |
|------|------|---------|
| `graph.h` | C++ Header | Graph ADT definition |
| `main.cpp` | C++ Source | Program entry point |
| `bfs_dfs.cpp` | C++ Source | BFS/DFS implementations |
| `dijkstra.cpp` | C++ Source | Dijkstra's algorithm |
| `bellman_ford.cpp` | C++ Source | Bellman-Ford algorithm |
| `kruskal.cpp` | C++ Source | Kruskal's MST algorithm |
| `experimental.cpp` | C++ Source | Performance testing |
| `Makefile` | GNU Make | Build automation |

### Results & Analysis
| File | Type | Purpose |
|------|------|---------|
| `output.html` | HTML | Formatted program output |
| `experimental_results.md` | Markdown | Performance benchmarks |

---

## 📊 Project Key Metrics

**Network:**
- 20 routers (vertices R0–R19)
- 33 directed edges
- Weights: latency in milliseconds

**Algorithms:**
1. **BFS** — O(V+E) traversal
2. **DFS** — O(V+E) traversal
3. **Dijkstra** — O((V+E) log V) shortest path
4. **Bellman-Ford** — O(V×E) shortest path (supports negatives)
5. **Kruskal** — O(E log E) MST

**Performance Highlights:**
- Shortest path (R0→R19): **49ms**
- MST total weight: **171ms**
- BFS/DFS execution: **< 1 microsecond**

---

## ✅ Submission Checklist

Use this checklist before submitting:

- [ ] **Presentation** — `COT4400_Presentation.pptx` present
- [ ] **Report (PDF)** — `COT4400_Report.pdf` present
- [ ] **Report (Word)** — `COT4400_Report.docx` present
- [ ] **Source Code** — All `.cpp` and `.h` files included
- [ ] **Build System** — `Makefile` present and functional
- [ ] **Program Output** — `output.html` generated correctly
- [ ] **Results** — `experimental_results.md` complete
- [ ] **Documentation** — `complexity_analysis.md` included
- [ ] **Compilation Test** — `make` runs without errors
- [ ] **Execution Test** — `./router_network` produces all 7 sections

---

## 🔧 System Requirements

| Requirement | Version |
|-------------|---------|
| Compiler | g++ with C++17 |
| Build Tool | GNU Make 3.81+ |
| Platform | Linux / macOS / Windows (WSL) |

**Compile Command:**
```bash
g++ -std=c++17 -O2 -Wall -Wextra
```

---

## 📝 File Descriptions

### Source Files

**graph.h**
- Graph class implementation using adjacency list
- Edge list for MST algorithms
- Vertex count: 20 (R0–R19)

**main.cpp**
- Program entry point
- Builds the 20-router network
- Orchestrates all 7 algorithm sections
- ~8KB

**bfs_dfs.cpp**
- Breadth-First Search implementation
- Depth-First Search implementation
- Both traverse from source R0
- ~6KB

**dijkstra.cpp**
- Single-source shortest path
- Uses priority queue (binary heap)
- O((V+E) log V) complexity
- Does NOT support negative weights
- ~6KB

**bellman_ford.cpp**
- Single-source shortest path
- Supports negative edge weights
- Includes negative cycle detection
- Early termination optimization
- ~7KB

**kruskal.cpp**
- Minimum Spanning Tree algorithm
- Uses Union-Find data structure
- Treats graph as undirected
- O(E log E) complexity
- ~8KB

**experimental.cpp**
- Performance benchmarking suite
- Tests on 4 graph configurations
- Measures execution time via std::chrono
- ~14KB

---

## 📊 Output Structure

The program generates **7 sections** of output:

1. **Graph Adjacency List** — All 20 routers and 33 edges
2. **BFS Traversal** — Visit order from R0
3. **DFS Traversal** — Visit order from R0
4. **Dijkstra's Shortest Path** — All destinations from R0
5. **Bellman-Ford Shortest Path** — All destinations from R0
6. **Kruskal's MST** — 19 edges, 171ms total
7. **Experimental Performance** — Timing across 4 graph sizes

---

## 📥 How to Submit

### Option 1: Upload Folder Directly
Simply upload the entire `DELIVERABLES/` folder to your course management system.

### Option 2: Create a ZIP Archive
```bash
cd ..
zip -r COT4400_Final_Submission.zip DELIVERABLES/
```

Then submit `COT4400_Final_Submission.zip`

### Option 3: GitHub Link
Share the GitHub repository link with your instructor:
```
https://github.com/ZYXERO/COT4400-Router-Network-Optimization
```

---

## 📞 Support

**If compilation fails:**
1. Verify g++ version: `g++ --version` (should be 7.0+)
2. Check C++17 support: Try `g++ -std=c++17 -o test test.cpp`
3. Try explicit C++ standard: `make CXX=g++ CXXFLAGS="-std=c++17 -O2"`

**If execution fails:**
1. Ensure all `.cpp` files are present in `src/`
2. Check `Makefile` paths
3. Run `make clean` then `make` to rebuild

---

## 📄 Team Information

**Course:** COT-4400: Analysis of Algorithms  
**Institution:** USF Bellini College of AI, Cybersecurity & Computing  
**Team Members:**
- Seyoung Kan U — U36444259
- Kaushik Selvakumar — U75300364

**Submission Date:** April 25, 2026  
**Status:** ✅ Ready for Submission

---

**Last Updated:** April 25, 2026 | Package Version: 1.0
