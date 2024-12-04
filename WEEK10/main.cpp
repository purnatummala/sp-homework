#include <iostream>
#include "utils.h"

extern double parallel_trapezoidal(std::function<double(double)>, double, double, int, int);
extern double parallel_adaptive(std::function<double(double)>, double, double, double, int);

int main() {
    auto f1 = [](double x) { return x * x * x - 3 * x * x + 2; };
    auto f2 = [](double x) { return std::sqrt(x) * std::pow(1 - x, 2); };

    int num_threads = 4;
    int n = 100000;
    double tol = 1e-6;

    Timer timer;

    // Non-Adaptive
    timer.start();
    double result1 = parallel_trapezoidal(f1, 0, 2, n, num_threads);
    timer.stop();
    log_results("results/performance.csv", "Non-Adaptive", num_threads, timer.elapsed_ms());
    std::cout << "Non-Adaptive Result: " << result1 << ", Time: " << timer.elapsed_ms() << " ms\n";

    // Adaptive
    timer.start();
    double result2 = parallel_adaptive(f2, 0, 1, tol, num_threads);
    timer.stop();
    log_results("results/performance.csv", "Adaptive", num_threads, timer.elapsed_ms());
    std::cout << "Adaptive Result: " << result2 << ", Time: " << timer.elapsed_ms() << " ms\n";

    return 0;
}
