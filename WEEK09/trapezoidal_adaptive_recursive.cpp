#include <functional>
#include <iostream>
#include <cmath>  // For std::abs

using Function = std::function<double(double)>;

// Basic Trapezoidal Rule for an interval
double basicTrapezoidal(const Function &f, double a, double b)
{
    return 0.5 * (b - a) * (f(a) + f(b));
}

// Adaptive Trapezoidal Recursive Integration
double adaptiveTrapezoidalRecursive(const Function &f, double a, double b, double tol, int maxDepth, int depth)
{
    if (depth >= maxDepth)
    {
        return basicTrapezoidal(f, a, b);
    }

    double c = (a + b) / 2;
    double fa = f(a);
    double fb = f(b);
    double fc = f(c);

    double whole = (b - a) * (fa + fb) / 2;
    double left = (c - a) * (fa + fc) / 2;
    double right = (b - c) * (fc + fb) / 2;

    double error = std::abs(left + right - whole);

    if (error < tol)
    {
        return left + right;
    }

    return adaptiveTrapezoidalRecursive(f, a, c, tol / 2, maxDepth, depth + 1) +
           adaptiveTrapezoidalRecursive(f, c, b, tol / 2, maxDepth, depth + 1);
}

//----------------------------------------------------------------------
int main()
{
    const Function f = [](double x) { return x * x; };

    double result = adaptiveTrapezoidalRecursive(f, 2.0, 10.0, 1.e-7, 7, 0);
    std::cout << "Integral: " << result << std::endl;
    std::cout << "Exact: " << (1000 - 2 * 2 * 2) / 3.0 << std::endl;

    return 0;
}
//----------------------------------------------------------------------
