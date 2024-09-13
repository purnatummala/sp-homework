

# Homework 02

## Project Overview

This project involves the implementation of a `Vector` class and a `Particle` class in C++ to simulate and visualize the motion of particles in 2D and 3D space. The `Vector` class supports various operations, including addition, subtraction, scalar multiplication, and dot product. The `Particle` class models a particle with mass, position, velocity, and force, and allows for updating the particle's state over time.

### Key Features

- **Vector Class**: Supports 2D and 3D vectors with overloaded operators for addition, subtraction, scalar multiplication, and dot product.
- **Particle Class**: Models particles with position, velocity, and force. It can update the particle's state and print its current properties.
- **Trajectory Simulation**: Simulates the trajectories of particles in 2D and 3D space and writes the results to text files.
- **Plotting**: Generates plots of the particle trajectories using a Python script.

## How AI Was Used

During the development of this project, GPT-4-o was utilized to:

1. **Generate Test Cases**: Provided various scenarios and edge cases to thoroughly test the functionality of the `Vector` class.
2. **Debugging**: Assisted in identifying and resolving errors related to vector operations and file handling.
3. **Documentation**: Helped structure and write the README and explanations for the code.

## Errors Encountered and Resolutions

1. **Index Out of Bounds Error**:
   - **Issue**: Accessing vector components with invalid indices resulted in runtime errors.
   - **Resolution**: Added bounds checking in the `operator[]` to ensure indices are within valid ranges.

2. **File Handling Error**:
   - **Issue**: Errors opening files for writing trajectory data.
   - **Resolution**: Added checks to ensure files are opened successfully before attempting to write data.

3. **Python Plotting Script Error**:
   - **Issue**: Error in running the Python script to generate plots.
   - **Resolution**: Verified the script path and ensured Python was correctly installed and accessible.

## Plot Visualizations

Below are the generated plots of the 2D and 3D particle trajectories:

### 2D Particle Trajectory

![2D Particle Trajectory](images/trajectory_2D.png)

### 3D Particle Trajectory

![3D Particle Trajectory](images/trajectory_3D.png)

## Compilation and Execution

To compile and run the project, use the provided `Makefile`. Run the following commands in the project directory:

```sh
nmake #compile and runs the code 
nmake clean #clean the objects
homework2_skeleton.exe  # executes the  code
