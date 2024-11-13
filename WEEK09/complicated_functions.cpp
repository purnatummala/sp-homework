#include <cmath>
#include <stdexcept>
#include <iostream>

// Initialize with basic functions
double f1(double x)
{ return std::exp(-x * x) * std::sin(1000 * x); }

double f2(double x)
{ return std::pow(x, 0.75) * std::log(1 + x * x); }

double f3(double x)
{ return std::pow(x, 10) * std::exp(std::pow(x, 3)); }

double f4(double x)
{ return std::sin(std::cos(x * x)) * std::sinh(x); }

double f5(double x)
{ return std::exp(-x * x) * std::sin(1000 * std::exp(-x) * std::cos(200 * x)); }

double f6(double x)
{ return std::pow(x, 15) * std::exp(std::pow(x, 3) * std::log(1 + x * x)) * std::sin(std::sqrt(x) * std::exp(x)); }

double f7(double x)
{ return std::cosh(std::sin(x * x + std::exp(-x))) * std::pow(x, 2.5) * std::exp(x * x) * std::sin(std::cosh(x) * std::log(x * x + 1)); }

