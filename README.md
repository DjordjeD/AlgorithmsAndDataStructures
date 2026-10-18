# Algorithms and Data Structures

Assignments from the Algorithms and Data Structures course (ASP) at ETF Belgrade, 2019/20.

## Labyrinth solver (Floyd–Warshall)

Reads a maze, turns every cell into a graph node and runs Floyd–Warshall to find the shortest path from the entrance (*ulaz*) to the exit (*izlaz*). The path-reconstruction matrix is kept alongside the distance matrix, so the full route can be printed and not just its length.

```
Labyrinth solver using Floyd Warshall algorithm/
├── Labyrinth solver using Floyd-Warshall alg.cpp   # solution
└── 13E112ASP_DZ_1920.pdf                           # assignment spec (Serbian)
```

### Build

```bash
g++ -std=c++11 "Labyrinth solver using Floyd Warshall algorithm/Labyrinth solver using Floyd-Warshall alg.cpp" -o labyrinth
./labyrinth
```

Identifiers and console output are in Serbian.
