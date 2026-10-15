# Automation & Robotics C++ Portfolio

A small portfolio of C++ projects completed while studying Automation and Robotics Engineering at Algonquin College.

## Projects

### 1. Robotic Arm Forward Kinematics
Calculates a robotic arm's end-effector X, Y, and Z position from joint angles using 3D rotation matrices, matrix multiplication, coordinate transformations, and physical joint offsets. Includes joint-angle validation and a table-boundary safety check.

### 2. Matrix Computation Toolkit
A menu-driven linear-algebra application for 2x2 and 3x3 matrices. Supports determinants, inverses, transposes, singularity checks, and solving systems in the form Ax = b.

### 3. Stack & Queue Student Records
Custom stack and queue implementations built with `std::vector` and a `Student` class. Demonstrates LIFO/FIFO behavior and common operations such as push, pop, enqueue, dequeue, front, back, and size checks.

### 4. Vector Management App
Interactive C++ program demonstrating dynamic `std::vector` operations including insertion, removal, `push_back`, and `pop_back`.

## Build

Each project can be compiled independently with a C++17 compiler. Example:

```bash
g++ -std=c++17 robotic-arm-forward-kinematics/src/main.cpp -o forward_kinematics
./forward_kinematics
```

## About this portfolio

These projects were completed and refined as part of my Automation and Robotics Engineering studies. Source files are organized and documented for portfolio presentation while preserving the core project functionality.
