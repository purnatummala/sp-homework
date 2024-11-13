#ifndef INTEGRATION_OPERATOR_OVERLOADING_H
#define INTEGRATION_OPERATOR_OVERLOADING_H

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

public:
    // Constructor for adaptive integration
    AdaptiveIntegration(double a, double b, bool isRecursive, double absErrorTolerance, int maxAdaptDepth)
        : Integration(a, b, isRecursive, true), absErrorTolerance(absErrorTolerance), maxAdaptDepth(maxAdaptDepth) {}

    // Implementation of the integrate method
    double integrate(Function& func) override {
        // Placeholder implementation - you can replace this with actual adaptive integration logic
        double result = 0.0;
        // Perform adaptive integration here
        return result;
    }

    // Get method name for benchmarking purposes
    std::string getMethodName() const override {
        return "Adaptive Integration";
    }
};

#endif // INTEGRATION_OPERATOR_OVERLOADING_H
