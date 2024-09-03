#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

// Function to parse command-line arguments
bool parseArguments(int argc, char* argv[], int& N, float& a, float& b, float& dt, int& timeSteps, std::string& outputFile) {
    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " <grid size N> <a> <b> <time step dt> <number of time steps> <output file>\n";
        return false;
    }
    std::stringstream ss;
    
    // Parse grid size N
    ss << argv[1];
    if (!(ss >> N) || N <= 0) {
        std::cerr << "Error: Invalid grid size N. It must be a positive integer.\n";
        return false;
    }
    ss.clear();
    
    // Parse a
    ss << argv[2];
    if (!(ss >> a)) {
        std::cerr << "Error: Invalid value for a.\n";
        return false;
    }
    ss.clear();
    
    // Parse b
    ss << argv[3];
    if (!(ss >> b) || b <= a) {
        std::cerr << "Error: Invalid value for b. It must be greater than a.\n";
        return false;
    }
    ss.clear();
    
    // Parse time step dt
    ss << argv[4];
    if (!(ss >> dt) || dt <= 0) {
        std::cerr << "Error: Invalid time step dt. It must be a positive number.\n";
        return false;
    }
    ss.clear();
    
    // Parse number of time steps
    ss << argv[5];
    if (!(ss >> timeSteps) || timeSteps <= 0) {
        std::cerr << "Error: Invalid number of time steps. It must be a positive integer.\n";
        return false;
    }
    
    // Parse output file
    outputFile = argv[6];
    if (outputFile.empty()) {
        std::cerr << "Error: Output file name cannot be empty.\n";
        return false;
    }
    
    return true;
}

// Function to initialize the grid with T = 1 - x^2
std::vector<float> initializeGrid(int N, float a, float b) {
    std::vector<float> grid(N);
    float dx = (b - a) / (N - 1);
    for (int i = 0; i < N; ++i) {
        float x = a + i * dx;
        grid[i] = 1.0f - x * x;
    }
    return grid;
}

// Function to perform the time-stepping for heat distribution
void timeStepHeatDistribution(std::vector<float>& grid, float dt, int timeSteps, float dx) {
    std::vector<float> newGrid = grid;
    float alpha = dt / (dx * dx); // Thermal diffusivity coefficient
    for (int t = 0; t < timeSteps; ++t) {
        for (size_t i = 1; i < grid.size() - 1; ++i) {
            newGrid[i] = grid[i] + alpha * (grid[i - 1] - 2 * grid[i] + grid[i + 1]);
        }
        grid = newGrid;
    }
}

// Function to write the grid to a file
void writeGridToFile(const std::vector<float>& grid, float a, float b, const std::string& outputFile) {
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error opening output file: " << outputFile << "\n";
        return;
    }
    float dx = (b - a) / (grid.size() - 1);
    for (size_t i = 0; i < grid.size(); ++i) {
        float x = a + i * dx;
        outFile << x << " " << grid[i] << "\n";
    }
    outFile.close();
}

int main(int argc, char* argv[]) {
    int N;
    float a, b, dt;
    int timeSteps;
    std::string outputFile;

    if (!parseArguments(argc, argv, N, a, b, dt, timeSteps, outputFile)) {
        return 1;
    }

    std::vector<float> grid = initializeGrid(N, a, b);
    float dx = (b - a) / (N - 1);

    // Perform time-stepping for heat distribution
    timeStepHeatDistribution(grid, dt, timeSteps, dx);

    writeGridToFile(grid, a, b, outputFile);

    std::cout << "Time-dependent heat distribution simulation completed and written to " << outputFile << "\n";
    return 0;
}