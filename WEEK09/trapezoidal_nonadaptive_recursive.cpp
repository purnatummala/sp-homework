#include <iostream>
#include <functional>
#include <cmath>  // For std::abs

//----------------------------------------------------------------------

using Function = std::function<double(double)>;

// Basic Trapezoidal Rule for an interval
double basicTrapezoidal(const Function &f, double a, double b)
{
    return 0.5 * (b - a) * (f(a) + f(b));
}

// Trapezoidal Non-Adaptive Recursive Integration
double trapezoidalRecursive(const Function &f, double a, double b, double tol, int maxDepth, int depth)
{
    if (depth >= maxDepth)
    {
        return basicTrapezoidal(f, a, b);
    }

    double c = (a + b) / 2;

    double one_trap = basicTrapezoidal(f, a, b);
    double two_trap = basicTrapezoidal(f, a, c) + basicTrapezoidal(f, c, b);

    double error = std::abs(two_trap - one_trap);

    if (error < tol)
    {
        return two_trap;
    }

    return trapezoidalRecursive(f, a, c, tol / 2, maxDepth, depth + 1) +
           trapezoidalRecursive(f, c, b, tol / 2, maxDepth, depth + 1);
}

//----------------------------------------------------------------------

int main()
{
    const Function f = [](double x) { return x * x; };

    double result = trapezoidalRecursive(f, 2, 10, 1.e-8, 7, 0);
    std::cout << "Integral: " << result << std::endl;
    std::cout << "Exact: " << (1000 - 2 * 2 * 2) / 3.0 << std::endl;

    return 0;
}
//----------------------------------------------------------------------
