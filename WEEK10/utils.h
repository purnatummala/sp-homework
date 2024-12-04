#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

// Timing utility
class Timer {
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    double elapsed_ms() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time, end_time;
};

// Math utility for calculating mean and standard deviation
void calculate_mean_std(const std::vector<double>& data, double& mean, double& std_dev);

// Logging utility for performance data
void log_results(const std::string& filename, const std::string& method, int threads, double time);

#endif // UTILS_H
