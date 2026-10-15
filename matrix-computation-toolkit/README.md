# Matrix Computation Toolkit

## Overview
A menu-driven C++ linear-algebra program using nested `std::vector` containers to represent 2x2 and 3x3 matrices.

## Features
- Determinants for 2x2 and 3x3 matrices
- Matrix inverses
- Matrix transposes
- Singularity detection using a small floating-point tolerance
- Solution of 2x2 and 3x3 systems in the form `Ax = b`
- Menu-driven console interface

## Build and run
```bash
g++ -std=c++17 src/main.cpp -o matrix_toolkit
./matrix_toolkit
```

## Skills demonstrated
C++, STL vectors, functions, nested loops, linear algebra, numerical checks, modular programming, and user-input handling.
