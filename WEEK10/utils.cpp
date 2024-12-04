#include "utils.h"

void calculate_mean_std(const std::vector<double>& data, double& mean, double& std_dev) {
    mean = 0.0;
    for (const auto& val : data) {
        mean += val;
    }
    mean /= data.size();

    std_dev = 0.0;
    for (const auto& val : data) {
        std_dev += (val - mean) * (val - mean);
    }
    std_dev = std::sqrt(std_dev / data.size());
}

void log_results(const std::string& filename, const std::string& method, int threads, double time) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << method << "," << threads << "," << time << "\n";
        file.close();
    } else {
        std::cerr << "Error: Could not open file " << filename << "\n";
    }
}
