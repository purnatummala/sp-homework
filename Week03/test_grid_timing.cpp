#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <fstream>
#include "grid3d_1d_array.h"
#include "grid3d_vector.h"
#include "grid3d_new.h"

double measure_execution_time(int n) {
    Grid1 grid(n, n, n);
    auto start = std::chrono::high_resolution_clock::now();
    Grid1 grid_sum = grid + grid;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

void execute_timings() {
    std::vector<int> sizes = {10, 50, 100, 200};
    std::vector<double> times;

    for (int n : sizes) {
        std::vector<double> measurements;
        for (int i = 0; i < 5; ++i) {
            double time = measure_execution_time(n);
            if (i > 0) { // Discard the first timing
                measurements.push_back(time);
            }
        }
        double average_time = std::accumulate(measurements.begin(), measurements.end(), 0.0) / measurements.size();
        times.push_back(average_time);
    }

    // Print the results
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::cout << "Size: " << sizes[i] << ", Time: " << times[i] << " seconds" << std::endl;
    }

    // Save the results to a file for plotting
    std::ofstream outfile("timing_results.txt");
    for (size_t i = 0; i < sizes.size(); ++i) {
        outfile << sizes[i] << " " << times[i] << std::endl;
    }
    outfile.close();
}

int main() {
    std::cout << "Program started." << std::endl;
    execute_timings();
    std::cout << "Program finished." << std::endl;
    return 0;
}