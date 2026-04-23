# ============================================================
# File:    Makefile
# Project: Internet Router Network Optimization
# Course:  COT-4400 Analysis of Algorithms — USF Bellini College
# Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall
TARGET   = router_network
SRCDIR   = src

SOURCES  = $(SRCDIR)/main.cpp \
           $(SRCDIR)/bfs_dfs.cpp \
           $(SRCDIR)/dijkstra.cpp \
           $(SRCDIR)/bellman_ford.cpp \
           $(SRCDIR)/kruskal.cpp \
           $(SRCDIR)/experimental.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
