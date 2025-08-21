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

## Sample run:

**Input Polynomial and Prime:**

```
p = 2
f(x) = 4x^5 - 3x^3 + x^2 - 8x + 6
```

**Terminal output:**

```
All Points:
(0, 1)
(1, 0)
(2, 2)
(3, 0)
(4, 1)

Convex Hull:
(0, 1)
(1, 0)
(3, 0)
(4, 1)

Latticed Hull:
(0, 1)
(1, 0)
(2, 0)
(3, 0)
(4, 1)

Newton Polygon result numbers:
1 2 1 1
```

**Explanation:**

- All Points: Calculated nu-values for each coefficient.

- Convex Hull: Lower boundary of the Newton Polygon.

- Latticed Hull: Convex Hull plus lattice points in between.


- Result Numbers: Differences in x-coordinates between consecutive points in the latticed hull.





