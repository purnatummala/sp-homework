#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <numeric>
#include <chrono>
#include <fstream>
#include <mutex>

// Define the function to integrate
double f(double x) {
    return x * x * x - 3 * x * x + 2;
}

// Implement the trapezoidal rule for a subinterval (Sequential)
double sequential_trapezoidal(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double integral = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; ++i) {
        integral += f(a + i * h);
    }
    integral *= h;
    return integral;
}

// Parallelize the computation using threads (Parallel Non-Adaptive Trapezoidal)
void parallel_trapezoidal(double (*f)(double), double a, double b, int n, int t, double& total_integral, double& mean_eval, double& std_eval, double& mean_time, double& std_time) {
    auto worker = [](double (*f)(double), double start, double end, int step, double& result, int& eval_count, double& time) {
        auto start_time = std::chrono::high_resolution_clock::now();
        eval_count = step + 1;
        result = sequential_trapezoidal(f, start, end, step);
        auto end_time = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double>(end_time - start_time).count();
    };

    double h = (b - a) / n;
    int step = n / t;
    std::vector<std::thread> threads;
    std::vector<double> results(t);
    std::vector<int> eval_counts(t);
    std::vector<double> times(t);

    for (int i = 0; i < t; ++i) {
        double start = a + i * step * h;
        double end = (i == t - 1) ? b : start + step * h;
        threads.emplace_back(worker, f, start, end, step, std::ref(results[i]), std::ref(eval_counts[i]), std::ref(times[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    total_integral = std::accumulate(results.begin(), results.end(), 0.0);
    mean_eval = std::accumulate(eval_counts.begin(), eval_counts.end(), 0.0) / t;
    std_eval = std::sqrt(std::accumulate(eval_counts.begin(), eval_counts.end(), 0.0, [mean_eval](double sum, int val) { return sum + (val - mean_eval) * (val - mean_eval); }) / t);
    mean_time = std::accumulate(times.begin(), times.end(), 0.0) / t;
    std_time = std::sqrt(std::accumulate(times.begin(), times.end(), 0.0, [mean_time](double sum, double val) { return sum + (val - mean_time) * (val - mean_time); }) / t);
}

// Test the implementation with different configurations
int main() {
    std::vector<int> n_values = {1000, 10000, 100000};
    std::vector<int> t_values = {1, 2, 4, 8, 16};

    std::ofstream csv_file("parallel_trapezoidal_results.csv");
    csv_file << "n,threads,parallel_result,sequential_result,error,execution_time,mean_eval,std_eval,mean_time,std_time\n";

    for (int n : n_values) {
        // Calculate the sequential result for verification
        double sequential_result = sequential_trapezoidal(f, 0, 2, n);

        for (int t : t_values) {
            double total_integral, mean_eval, std_eval, mean_time, std_time;
            auto start_time = std::chrono::high_resolution_clock::now();
            parallel_trapezoidal(f, 0, 2, n, t, total_integral, mean_eval, std_eval, mean_time, std_time);
            auto end_time = std::chrono::high_resolution_clock::now();
            double execution_time = std::chrono::duration<double>(end_time - start_time).count();

            // Calculate error between parallel and sequential result
            double error = std::abs(total_integral - sequential_result);

            // Write results to CSV
            csv_file << n << "," << t << "," << total_integral << "," << sequential_result << "," << error << ",";
            csv_file << execution_time << "," << mean_eval << "," << std_eval << "," << mean_time << "," << std_time << "\n";
        }
    }

    csv_file.close();
    std::cout << "Results saved to parallel_trapezoidal_results.csv" << std::endl;

    return 0;
}
