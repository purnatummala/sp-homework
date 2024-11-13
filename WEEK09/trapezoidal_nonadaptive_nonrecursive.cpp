#include <iostream>
#include <functional>

using Function = std::function<double(double)>;

// Trapezoidal Non-Adaptive Non-Recursive Integration
double trapezoidalNonRecursive(const Function &f, double a, double b, int n_intervals)
{
    double h = (b - a) / n_intervals;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n_intervals; i++)
    {
        double x = a + i * h;
        sum += f(x);
    }

    return h * sum;
}

//----------------------------------------------------------------------

int main()
{
    const Function f = [](double x) { return x * x; };

    double result = trapezoidalNonRecursive(f, 2, 10, 1000);
    std::cout << "Integral: " << result << std::endl;
    std::cout << "Exact: " << (1000 - 2 * 2 * 2) / 3.0 << std::endl;

    return 0;
}
//----------------------------------------------------------------------
