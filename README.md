# Grid3D Project

## Overview

This project demonstrates the creation and manipulation of three-dimensional grids using different storage techniques: 

1. **Grid1** - Uses a 1D array for storing 3D data.
2. **Grid2** - Uses a vector-based approach for 3D grid data.
3. **Grid3** - An alternative approach for handling 3D grid data (details of implementation depend on the `grid3d_new.h` file).

The program performs the following:
- Initializes grids with specified dimensions (`nx`, `ny`, `nz`).
- Populates grids with values based on index calculations.
- Prints grid sizes and memory usage.
- Demonstrates grid addition using operator overloading.

## Files

- `grid3d_1d_array.h`: Header file for 3D grid implementation using a 1D array.
- `grid3d_vector.h`: Header file for 3D grid implementation using a vector.
- `grid3d_new.h`: Header file for an alternate 3D grid implementation.
- `main.cpp`: Contains the main function
- `test_grid.cpp`: contains test cases for checking the functionality of different grid implementations.

## How to Run

1. Clone the repository or download the source code.
2. Ensure all required header files (`grid3d_1d_array.h`, `grid3d_vector.h`, and `grid3d_new.h`) are in the same directory as `main.cpp`.
3. Compile the code using a C++ compiler. Example for `g++`:
   ```bash
    g++ -o main main.cpp Grid1.cpp Grid2.cpp Grid3.cpp
   ./main

## OUTPUT
The output looks like 
Program started.
grid size: 24
grid memory: 192 bytes
Grid 1:          0        100 
        10        110 
        20        120

         1        101
        11        111
        21        121

         2        102
        12        112
        22        122

         3        103
        13        113
        23        123

grid size: 24
grid memory: 192 bytes
Grid 2:          0        100 
        10        110
        20        120

         1        101
        11        111
        21        121

         2        102
        12        112
        22        122

         3        103
        13        113
        23        123

grid size: 24
grid memory: 192 bytes
Grid 3:          0        100
        10        110
        20        120

         1        101
        11        111 
        21        121

         2        102
        12        112
        22        122

         3        103
        13        113
        23        123

Program finished.
