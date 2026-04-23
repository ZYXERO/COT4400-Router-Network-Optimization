# ============================================================
# File:    Makefile
# Project: Internet Router Network Optimization
# Course:  COT-4400 Analysis of Algorithms — USF Bellini College
# Team:    Seyoung Kan U (U36444259) | Kaushik Selvakumar (U75300364)
# ============================================================
#
# Usage:
#   make          — compile the project (default target: all)
#   make run      — compile and run the binary
#   make clean    — remove compiled objects and binary
# ============================================================

# Compiler and standard
CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

# Output binary name
TARGET = router_network

# Source files (all .cpp files in the project)
SRCS = main.cpp bfs_dfs.cpp dijkstra.cpp bellman_ford.cpp kruskal.cpp experimental.cpp

# Object files (derived from source file names)
OBJS = $(SRCS:.cpp=.o)

# ============================================================
# Default target: compile everything
# ============================================================
all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile each .cpp file to a .o object file
# $< = the prerequisite (source file)
# $@ = the target (object file)
%.o: %.cpp graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
# run target: compile and execute the binary
# ============================================================
run: all
	./$(TARGET)

# ============================================================
# clean target: remove all compiled artifacts
# ============================================================
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned build artifacts."

# Declare non-file targets to avoid conflicts with files of the same name
.PHONY: all run clean
