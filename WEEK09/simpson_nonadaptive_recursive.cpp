#include <iostream>
#include <functional>
#include <cmath>  // For std::abs

using Function = std::function<double(double)>;

// Basic Simpson's Rule for an interval
double basicSimpson(const Function &f, double a, double b)
{
    double h = (b - a) / 2;
    double mid = (a + b) / 2;
    return (h / 3) * (f(a) + 4 * f(mid) + f(b));
}

// Simpson's Non-Adaptive Recursive Integration
double simpsonNonAdaptiveRecursive(const Function &f, double a, double b, double tol, int maxDepth, int depth)
{
    if (depth >= maxDepth)
    {
        return basicSimpson(f, a, b);
    }

    double c = (a + b) / 2;
    double fa = f(a);
    double fb = f(b);
    double fc = f(c);

    double whole = (b - a) * (fa + 4 * fc + fb) / 6;
    double left = (c - a) * (fa + 4 * f((a + c) / 2) + fc) / 6;
    double right = (b - c) * (fc + 4 * f((c + b) / 2) + fb) / 6;

    double error = std::abs(left + right - whole);

    if (error < tol)
    {
        return left + right;
    }

    return simpsonNonAdaptiveRecursive(f, a, c, tol / 2, maxDepth, depth + 1) +
           simpsonNonAdaptiveRecursive(f, c, b, tol / 2, maxDepth, depth + 1);
}

//----------------------------------------------------------------------

int main()
{
    const Function f = [](double x) { return x * x; };

    double result = simpsonNonAdaptiveRecursive(f, 2.0, 10.0, 1.e-7, 10, 0);
    std::cout << "Integral: " << result << std::endl;
    std::cout << "Exact: " << (1000 - 2 * 2 * 2) / 3.0 << std::endl;

    return 0;
}
//----------------------------------------------------------------------