#include <iostream>
#include <functional>
#include <chrono>
#include <cmath>  // For std::fabs and std::round
#include <vector>  // For std::vector
#include "definitions.h"

class Integration {
protected:
    double a, b;  // Integration bounds
    bool isRecursive;  // Whether the integration is recursive
    bool isAdaptive;  // Whether the integration is adaptive
    double executionTime;  // Time taken to perform integration
    int functionEvaluations;  // Number of function evaluations

public:
    // Constructor to initialize bounds and integration type
    Integration(double a, double b, bool isRecursive, bool isAdaptive)
        : a(a), b(b), isRecursive(isRecursive), isAdaptive(isAdaptive), executionTime(0.0), functionEvaluations(0) {}

    // Pure virtual function to integrate - must be implemented by derived classes
    virtual double integrate(Function& func) = 0;

    // Operator () to call integrate and measure execution time
    double operator()(Function& func) {
        auto start = std::chrono::high_resolution_clock::now();
        double result = integrate(func);
        auto end = std::chrono::high_resolution_clock::now();
        
        executionTime = std::chrono::duration<double>(end - start).count();
        functionEvaluations = func.getCount();
        return result;
    }

    // Get the execution time of the last integration
    double getExecutionTime() const {
        return executionTime;
    }

    // Get the number of function evaluations
    int getFunctionEvaluations() const {
        return functionEvaluations;
    }

    // Virtual destructor
    virtual ~Integration() = default;

    // Overloaded addition operator for combining contiguous integrations
    friend double operator+(Integration& lhs, Integration& rhs) {
        if (lhs.b != rhs.a) {
            throw std::invalid_argument("Intervals must be contiguous for addition.");
        }
        CachedFunction func([](double x) { return x * x; });  // Example function, modify as needed
        double lhsResult = lhs(func);
        double rhsResult = rhs(func);
        return lhsResult + rhsResult;
    }

    // Get method name for benchmarking purposes
    virtual std::string getMethodName() const = 0;
};

class NonAdaptiveIntegration : public Integration {
private:
    int numIntervals;

public:
    // Constructor for non-adaptive integration
    NonAdaptiveIntegration(double a, double b, bool isRecursive, int numIntervals)
        : Integration(a, b, isRecursive, false), numIntervals(numIntervals) {}

    // Implementation of the integrate method
    double integrate(Function& func) override {
        double result = 0.0;
        double h = (b - a) / numIntervals;
        for (int i = 0; i < numIntervals; ++i) {
            double x1 = a + i * h;
            double x2 = a + (i + 1) * h;
            result += 0.5 * h * (func.evaluate(x1) + func.evaluate(x2));
        }
        return result;
    }

    // Get method name for benchmarking purposes
    std::string getMethodName() const override {
        return "Non-Adaptive Integration";
    }
};

class AdaptiveIntegration : public Integration {
private:
    double absErrorTolerance;
    int maxAdaptDepth;

    // Recursive adaptive Simpson's rule implementation
    double adaptiveSimpson(Function& func, double a, double b, double tol, int depth) {
        double c = (a + b) / 2;
        double fa = func.evaluate(a);
        double fb = func.evaluate(b);
        double fc = func.evaluate(c);

        double h = (b - a) / 2;
        double S = (h / 3) * (fa + 4 * fc + fb);
        double left = (h / 6) * (fa + 4 * func.evaluate((a + c) / 2) + fc);
        double right = (h / 6) * (fc + 4 * func.evaluate((c + b) / 2) + fb);
        double error = std::fabs(left + right - S);

        if (error < 15 * tol || depth >= maxAdaptDepth) {
            return left + right + error / 15;
        }

        return adaptiveSimpson(func, a, c, tol / 2, depth + 1) +
               adaptiveSimpson(func, c, b, tol / 2, depth + 1);
    }

public:
    // Constructor for adaptive integration
    AdaptiveIntegration(double a, double b, bool isRecursive, double absErrorTolerance, int maxAdaptDepth)
        : Integration(a, b, isRecursive, true), absErrorTolerance(absErrorTolerance), maxAdaptDepth(maxAdaptDepth) {}

    // Implementation of the integrate method
    double integrate(Function& func) override {
        return adaptiveSimpson(func, a, b, absErrorTolerance, 0);
    }

    // Get method name for benchmarking purposes
    std::string getMethodName() const override {
        return "Adaptive Integration";
    }
};

void benchmarkMethod(Integration& method, Function& func, const std::string& functionName, double exactResult, const std::string& cacheType, bool cacheEnabled) {
    // Reset function evaluation count
    func.resetCounter();

    // Empty cache (assuming Function has a method to clear the cache)
    func.clearCache();

    // Run the integration
    double result = method(func);

    // Calculate absolute and relative error
    double absError = std::fabs(result - exactResult);
    double relError = absError / std::fabs(exactResult);

    // Output benchmark results
    std::cout << "Method Name: " << method.getMethodName() << "\n";
    std::cout << "Function Name: " << functionName << "\n";
    std::cout << "Cache Type: " << cacheType << "\n";
    std::cout << "Cache Enabled: " << (cacheEnabled ? "true" : "false") << "\n";
    std::cout << "Numerical Result: " << result << "\n";
    std::cout << "Absolute Error: " << absError << "\n";
    std::cout << "Relative Error: " << relError << "\n";
    std::cout << "Function Evaluations: " << method.getFunctionEvaluations() << "\n";
    std::cout << "Execution Time (sec): " << std::scientific << method.getExecutionTime() << "\n";
    std::cout << "-----------------------------\n";
}

int main() {
    // Define some test functions with known analytical integrals
    CachedFunction funcSin([](double x) { return std::sin(x); });
    double exactSin = -std::cos(1.0) + std::cos(0.0);  // Integral of sin(x) from 0 to 1

    CachedFunction funcLog([](double x) { return std::log(x); });
    double exactLog = 1.0 * std::log(1.0) - 1.0;  // Integral of log(x) from 1 to 2

    // Example usage of NonAdaptiveIntegration
    NonAdaptiveIntegration nonAdaptiveSin(0.0, 1.0, false, 100);
    benchmarkMethod(nonAdaptiveSin, funcSin, "sin(x)", exactSin, "slow", true);

    // Example usage of AdaptiveIntegration
    AdaptiveIntegration adaptiveLog(1.0, 2.0, true, 1.e-8, 12);
    benchmarkMethod(adaptiveLog, funcLog, "log(x)", exactLog, "fast", true);

    return 0;
}
