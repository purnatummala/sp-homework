#include <iostream>
#include <fstream>
#include <functional>
#include <chrono>
#include <cmath>  // For std::fabs and std::round
#include <vector>  // For std::vector
#include "definitions.h"
#include "integration_operator_overloading.h"

void runBenchmarks(std::ostream &output) {
    // List of functions to benchmark
    std::vector<CachedFunction> functions = {
        CachedFunction([](double x) { return std::sin(x); }, 1e-7),
        CachedFunction([](double x) { return std::log(x); }, 1e-7),
        CachedFunction([](double x) { return std::exp(-x * x) * std::sin(1000 * x); }, 1e-7)
    };
    
    std::vector<std::string> functionNames = {
        "sin(x)",
        "log(x)",
        "exp(-x^2) * sin(1000x)"
    };
    
    // Exact integral results for benchmarking (analytically known or approximated)
    std::vector<double> exactResults = {
        -std::cos(1.0) + std::cos(0.0),  // Integral of sin(x) from 0 to 1
        1.0 * std::log(1.0) - 1.0,       // Integral of log(x) from 1 to 2
        0.0                             // Placeholder for more complex functions
    };
    
    // List of integration methods
    NonAdaptiveIntegration trapezoidalNonAdaptive(0.0, 1.0, false, 2048);
    AdaptiveIntegration trapezoidalAdaptive(0.0, 1.0, true, 1.e-8, 12);
    NonAdaptiveIntegration simpsonNonAdaptive(0.0, 1.0, false, 2048);
    AdaptiveIntegration simpsonAdaptive(0.0, 1.0, true, 1.e-8, 12);
    
    std::vector<Integration*> methods = {
        &trapezoidalNonAdaptive,
        &trapezoidalAdaptive,
        &simpsonNonAdaptive,
        &simpsonAdaptive
    };
    
    std::vector<std::string> methodNames = {
        "Trapezoidal Non-Adaptive Integration",
        "Trapezoidal Adaptive Integration",
        "Simpson Non-Adaptive Integration",
        "Simpson Adaptive Integration"
    };

    // Run benchmarks for each function and each method, with different cache settings
    std::vector<std::string> cacheTypes = {"none", "slow", "fast"};
    for (size_t i = 0; i < functions.size(); ++i) {
        for (size_t j = 0; j < methods.size(); ++j) {
            for (const auto& cacheType : cacheTypes) {
                // Set cache type for the function
                if (cacheType == "none") {
                    functions[i].clearCache();
                }
                
                // Run benchmark and write to output
                output << "Method Name: " << methodNames[j] << "\n";
                output << "Function Name: " << functionNames[i] << "\n";
                output << "Cache Type: " << cacheType << "\n";
                output << "Cache Enabled: " << (cacheType != "none" ? "true" : "false") << "\n";
                double result = (*methods[j])(functions[i]);
                double absoluteError = std::abs(result - exactResults[i]);
                double relativeError = (exactResults[i] != 0.0) ? absoluteError / std::abs(exactResults[i]) : 0.0;
                output << "Numerical Result: " << result << "\n";
                output << "Absolute Error: " << absoluteError << "\n";
                output << "Relative Error: " << relativeError << "\n";
                output << "Function Evaluations: " << methods[j]->getFunctionEvaluations() << "\n";
                output << "Execution Time (sec): " << methods[j]->getExecutionTime() << "\n";
                output << "-----------------------------\n";
            }
        }
    }
}

int main() {
    // Open output file stream
    std::ofstream outFile("benchmark_results.txt");

    if (outFile.is_open()) {
        // Run the benchmarks and write to the file
        runBenchmarks(outFile);
        outFile.close();
        std::cout << "Benchmark results saved to 'benchmark_results.txt'." << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }

    return 0;
}
