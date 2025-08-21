# MST Builder

The **MST Builder** is an automation tool that constructs and calculates Minimum Spanning Trees from a user-inputted connected graph of any scale or size. It outputs the results of the calculated MST in the terminal and generates algorithmic actions to denote the operational process.

---

## Quick Download (Recommended)

For casual users, this only downloads an executable app for easy access, suited to your OS. This format removes the tedium of extra installations, configurations, or compilations.

***Important Note:*** For some systems with auto-protection or malware scanners, the executable may be flagged as unknown. For users to continue, simply bypass (ex. clicking "Run Anyway"). The source code is all in this repository and I assure all that this project has no harmful intentions.

[![Windows](https://img.shields.io/badge/Download-Windows-blue?style=for-the-badge&logo=windows)](https://github.com/hgd-dev/MST-Builder/actions/runs/17132621900/artifacts/3820767544)
[![macOS](https://img.shields.io/badge/Download-macOS-lightgrey?style=for-the-badge&logo=apple)](https://github.com/hgd-dev/MST-Builder/actions/runs/17132621900/artifacts/3820765405)
[![Linux](https://img.shields.io/badge/Download-Linux-yellow?style=for-the-badge&logo=linux)](https://github.com/hgd-dev/MST-Builder/actions/runs/17132621900/artifacts/3820814308)

***Caveat for all runs:*** This project has automatic input fail-safe detectors to ensure smooth running and correct input of data. While it is built-in to catch typos or mistaken keystrokes, please refrain from deliberately attempting to break the program or use corrupted data. Undefined behavior can have unintended consequences.

---

## Project Structure

```
MST-Builder/
├── .github/ # GitHub Actions workflows
│ └── workflows/
│ └── build.yml
├── CMakeLists.txt # Build configuration for CMake
├── kruskal.cpp # Kruskal source file
├── prim.cpp # Prim source file
└── build_mst.cpp # Single-file version of the project
```

---

## Features

- Constructs Minimum Spanning Trees from user-inputted connected graphs of any degree.  
- Outputs the vertices and edges of a resulting minimum spanning tree and step-by-step algorithm edge and vertex adding calculations in the terminal.  
- Cross-platform support: Windows, macOS, Linux.  
- Includes both multi-file CMake project and a single-file `build_mst.cpp` version.  

---

## Build and Run Instructions (From project source code)

### **Requirements**

| Component                       | Version / Notes                          |
|---------------------------------|-----------------------------------------|
| C++ Compiler                     | C++17 compatible                         |
| CMake                            | 3.10+                                    |
| Operating System                 | Windows, macOS, Linux                    |

---

### **1. Multi-file Project (CMake)**

**Build:**

```bash
git clone https://github.com/hgd-dev/MST-Builder.git
cd MST-Builder

mkdir build && cd build
cmake ..
make
```

**Run:**

```
./MSTBuilder
```

### **2. Single-file Version (build_mst.cpp)**

**Compile:**

```bash
# Linux/macOS
g++ -std=c++17 build_mst.cpp -o MSTBuilder

# Windows (MinGW example)
g++ -std=c++17 build_mst.cpp -o MSTBuilder.exe
```

**Run:**

```bash
./MSTBuilder   # or NewtonPolygonizer.exe on Windows
```

## Sample Terminal:

```

Welcome to MST Builder!

Select function from menu below to build a minimum spanning tree (MST):
  Enter k to execute Kruskal's MST Algorithm
  Enter p to execute Prim's MST Algorithm
  Enter b to execute both MST algorithms
  Enter e to exit this program
b

Key enter "b" detected.

Executing both algorithms:
Enter your graph's number of edges (╬╡(G)):
4
Input edge 1 in the form: node1 node2 weight
a b 1
Input edge 2 in the form: node1 node2 weight
b c 2
Input edge 3 in the form: node1 node2 weight
c a 3
Input edge 4 in the form: node1 node2 weight
b d 4
For Prim Algorithm: Enter any desired initial vertex, or "rand" for arbitrary choice:
rand

Starting Prim's MST Algorithm at vertex a:

Performing Prim Algorithm:

New edge added between nodes { a b } of weight 1
along with new node b

New edge added between nodes { b c } of weight 2
along with new node c

New edge added between nodes { b d } of weight 4
along with new node d


Performing Kruskal Algorithm:

New edge added between nodes { a b } of weight 1
along with new node a and new node b

New edge added between nodes { b c } of weight 2
along with new node c

New edge added between nodes { b d } of weight 4
along with new node d


List of MST Vertices:
a b c d

List of MST Edges (Prim):
  Nodes: { a b }, Weight: 1
  Nodes: { b c }, Weight: 2
  Nodes: { b d }, Weight: 4

List of MST Edges (Kruskal):
  Nodes: { a b }, Weight: 1
  Nodes: { b c }, Weight: 2
  Nodes: { b d }, Weight: 4
```





