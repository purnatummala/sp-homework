#ifndef SPECIFIC_FUNCTIONS_H
#define SPECIFIC_FUNCTIONS_H

#include "function.h"
#include <cmath>
#include <string>

// Define M_PI if it's not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// SinFunction class
template <typename T>
class SinFunction : public Function<T>
{
public:
    T f(T x) const override {
        return std::sin(3 * x - 2);
    }

    T df(T x) const override {
        return 3 * std::cos(3 * x - 2);  // Derivative of sin(3x - 2)
    }

    std::string name() const override {
        return "sin(3x - 2)";
    }
};

// PolynomialFunction class
template <typename T>
class PolynomialFunction : public Function<T>
{
public:
    T f(T x) const override {
        return x * x * x - 6 * x * x + 11 * x - 8;
    }

    T df(T x) const override {
        return 3 * x * x - 12 * x + 11;  // Derivative of x^3 - 6x^2 + 11x - 8
    }

    std::string name() const override {
        return "x^3 - 6x^2 + 11x - 8";
    }
};

// LogFunction class
template <typename T>
class LogFunction : public Function<T>
{
public:
    T f(T x) const override {
        return std::log(x) + x * x - 3;
    }

    T df(T x) const override {
        return 1 / x + 2 * x;  // Derivative of log(x) + x^2 - 3
    }

    std::string name() const override {
        return "log(x) + x^2 - 3";
    }
};

#endif