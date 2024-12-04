#include "utils.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cmath>
#include <functional>
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <atomic>
#include <numeric>
#include <fstream>

struct Task {
    double a, b, tol;
};

// Sequential Adaptive Trapezoidal Integration for Verification
double sequential_adaptive_trapezoidal(std::function<double(double)> f, double a, double b, double tol) {
    double c = (a + b) / 2.0;
    double fa = f(a), fb = f(b), fc = f(c);
    double I1 = (b - a) * (fa + fb) / 2.0;
    double I2 = (b - a) * (fa + 4 * fc + fb) / 6.0;
    if (std::abs(I2 - I1) < tol) {
        return I2;
    } else {
        return sequential_adaptive_trapezoidal(f, a, c, tol / 2.0) + sequential_adaptive_trapezoidal(f, c, b, tol / 2.0);
    }
}

class ThreadPool {
public:
    ThreadPool(size_t num_threads, std::function<double(double)> f);
    ~ThreadPool();
    void enqueue(Task task);
    void wait_for_completion();
    double get_result() const;
    void get_thread_statistics(double& mean_evaluations, double& stddev_evaluations, double& mean_time, double& stddev_time) const;

private:
    std::vector<std::thread> workers;
    std::queue<Task> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    std::atomic<int> active_tasks;
    double result;
    std::mutex result_mutex;
    std::function<double(double)> f;
    std::vector<std::atomic<int>> function_evaluations; // Track function evaluations per thread
    std::vector<std::chrono::duration<double>> thread_execution_times; // Track thread execution times

    void worker_thread(size_t thread_id);
};

ThreadPool::ThreadPool(size_t num_threads, std::function<double(double)> f) 
    : stop(false), result(0.0), f(f), active_tasks(0), function_evaluations(num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        function_evaluations[i] = 0;
        workers.emplace_back(&ThreadPool::worker_thread, this, i);
    }
    thread_execution_times.resize(num_threads);
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers) {
        worker.join();
    }
}

void ThreadPool::enqueue(Task task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.push(task);
        ++active_tasks;  // Increment the number of active tasks
    }
    condition.notify_one();
}

void ThreadPool::wait_for_completion() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    condition.wait(lock, [this] { return tasks.empty() && (active_tasks == 0); });
}

double ThreadPool::get_result() const {
    return result;
}

void ThreadPool::get_thread_statistics(double& mean_evaluations, double& stddev_evaluations, double& mean_time, double& stddev_time) const {
    int total_evaluations = std::accumulate(function_evaluations.begin(), function_evaluations.end(), 0);
    mean_evaluations = static_cast<double>(total_evaluations) / function_evaluations.size();

    double variance = 0.0;
    for (auto &eval : function_evaluations) {
        variance += std::pow(eval - mean_evaluations, 2);
    }
    variance /= function_evaluations.size();
    stddev_evaluations = std::sqrt(variance);

    double total_time = 0.0;
    for (const auto &time : thread_execution_times) {
        total_time += time.count();
    }
    mean_time = total_time / thread_execution_times.size();

    variance = 0.0;
    for (const auto &time : thread_execution_times) {
        variance += std::pow(time.count() - mean_time, 2);
    }
    variance /= thread_execution_times.size();
    stddev_time = std::sqrt(variance);
}

void ThreadPool::worker_thread(size_t thread_id) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Start timing before the loop
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) {
                break;  // Properly exit the loop, and record the end time after breaking
            }

            task = tasks.front();
            tasks.pop();
        }

        // Measure time spent on the task
        auto task_start_time = std::chrono::high_resolution_clock::now();

        // Process the task
        ++function_evaluations[thread_id]; // Increment function evaluation count for this thread

        double c = (task.a + task.b) / 2.0;
        double fa = f(task.a), fb = f(task.b), fc = f(c);
        double I1 = (task.b - task.a) * (fa + fb) / 2.0;
        double I2 = (task.b - task.a) * (fa + 4 * fc + fb) / 6.0;

        if (std::abs(I2 - I1) < task.tol) {
            std::unique_lock<std::mutex> lock(result_mutex);
            result += I2;
        } else {
            enqueue({task.a, c, task.tol / 2.0});
            enqueue({c, task.b, task.tol / 2.0});
        }

        --active_tasks;
        condition.notify_all();

        auto task_end_time = std::chrono::high_resolution_clock::now();
        thread_execution_times[thread_id] += (task_end_time - task_start_time);  // Accumulate time spent
    }
    auto end_time = std::chrono::high_resolution_clock::now();  // End timing after the loop
}

double parallel_adaptive(std::function<double(double)> f, double a, double b, double tol, int num_threads, double& mean_evaluations, double& stddev_evaluations, double& mean_time, double& stddev_time) {
    ThreadPool pool(num_threads, f);
    pool.enqueue({a, b, tol});
    pool.wait_for_completion();
    pool.get_thread_statistics(mean_evaluations, stddev_evaluations, mean_time, stddev_time);
    return pool.get_result();
}

int main() {
    auto f = [](double x) { return std::sqrt(x) * std::pow(1 - x, 2); };
    std::vector<int> thread_counts = {1, 2, 4, 8, 16};
    std::vector<double> tolerances = {1e-3, 1e-6};

    std::ofstream csv_file("adaptive_trapezoidal_results.csv");
    csv_file << "tolerance,threads,parallel_result,sequential_result,error,execution_time,mean_evaluations,stddev_evaluations,mean_time,stddev_time\n";

    for (double tol : tolerances) {
        // Calculate sequential result for verification
        double sequential_result = sequential_adaptive_trapezoidal(f, 0, 1, tol);

        for (int t : thread_counts) {
            double mean_evaluations, stddev_evaluations, mean_time, stddev_time;
            auto start_time = std::chrono::high_resolution_clock::now();
            double parallel_result = parallel_adaptive(f, 0, 1, tol, t, mean_evaluations, stddev_evaluations, mean_time, stddev_time);
            auto end_time = std::chrono::high_resolution_clock::now();
            double execution_time = std::chrono::duration<double>(end_time - start_time).count();

            // Calculate the error between sequential and parallel results
            double error = std::abs(parallel_result - sequential_result);

            // Write to CSV
            csv_file << tol << "," << t << "," << parallel_result << "," << sequential_result << "," << error << ",";
            csv_file << execution_time << "," << mean_evaluations << "," << stddev_evaluations << "," << mean_time << "," << stddev_time << "\n";
        }
    }

    csv_file.close();
    std::cout << "Results saved to adaptive_trapezoidal_results.csv" << std::endl;

    return 0;
}
