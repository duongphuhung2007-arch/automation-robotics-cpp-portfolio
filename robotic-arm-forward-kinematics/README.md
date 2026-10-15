# Robotic Arm Forward Kinematics

## Overview
This C++ project calculates the end-effector position of a multi-joint robotic arm from four input joint angles: waist, shoulder, elbow, and wrist pitch.

## What it demonstrates
- 3D rotation matrices about the X and Z axes
- 3x3 matrix multiplication
- Matrix-vector multiplication
- Coordinate transformations and link/joint offsets
- Conversion from servo angles to mathematical angles
- Input validation for 0-180 degree joint limits
- A workspace safety check that rejects positions below the table boundary

## Build and run
```bash
g++ -std=c++17 src/main.cpp -o forward_kinematics
./forward_kinematics
```

## Portfolio note
This version was lightly refactored from the academic project for clearer naming, formatting, and portability while preserving the original project behavior.
