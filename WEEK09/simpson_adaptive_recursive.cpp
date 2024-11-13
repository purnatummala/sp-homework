#include <functional>
#include <iostream>
#include <cmath> // Include cmath for std::log and std::abs

using Function = std::function<double(double)>;

// Basic Simpson's Rule for an interval
double basicSimpson(const Function &f, double a, double b)
{
    double h = (b - a) / 2;
    double mid = (a + b) / 2;
    return (h / 3) * (f(a) + 4 * f(mid) + f(b));
}

// Adaptive Simpson Recursive Integration
double adaptiveSimpsonRecursive(const Function &f, double a, double b, double tol, int maxDepth, int depth)
{
    if (depth >= maxDepth)
    {
        return basicSimpson(f, a, b);
    }

    double c = (a + b) / 2;
    double fa = f(a);
    double fb = f(b);
    double fc = f(c);

    double left_mid = (a + c) / 2;
    double right_mid = (c + b) / 2;
    double flm = f(left_mid);
    double frm = f(right_mid);

    double whole = (b - a) * (fa + 4 * fc + fb) / 6;
    double left = (c - a) * (fa + 4 * flm + fc) / 6;
    double right = (b - c) * (fc + 4 * frm + fb) / 6;

    double error = std::abs(left + right - whole);

    if (error < tol)
    {
        return left + right;
    }

    return adaptiveSimpsonRecursive(f, a, c, tol / 2, maxDepth, depth + 1) +
           adaptiveSimpsonRecursive(f, c, b, tol / 2, maxDepth, depth + 1);
}

//----------------------------------------------------------------------

int main()
{
    const Function f = [](double x)
    { return std::log(x); };
    const Function defInt = [](double x)
    { return x * std::log(x) - x; };

    double a = 1.0;
    double b = 10.0;
    double tol = 1e-8;
    int maxDepth = 8;

    double result = adaptiveSimpsonRecursive(f, a, b, tol, maxDepth, 0);
    double exact = defInt(b) - defInt(a);

    std::cout << "Adaptive Simpson's Rule Result: " << result << std::endl;
    std::cout << "Exact Integral: " << exact << std::endl;
    std::cout << "Error: " << std::abs(result - exact) << std::endl;

    return 0;
}
//----------------------------------------------------------------------
