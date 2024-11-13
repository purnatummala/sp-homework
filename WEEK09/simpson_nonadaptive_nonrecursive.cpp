#include <iostream>
#include <functional>

using Function = std::function<double(double)>;

// Simpson's Non-Adaptive Non-Recursive Integration
double simpsonNonRecursive(const Function &f, double a, double b, int n_intervals)
{
    int n = n_intervals;
    if (n % 2 != 0)
    {
        n++; // Ensure n is even
    }

    double h = (b - a) / n;
    double sum = f(a) + f(b); // First and last terms

    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        sum += (i % 2 == 0) ? 2 * f(x) : 4 * f(x);
    }

    return h * sum / 3;
}

//----------------------------------------------------------------------

int main()
{
    const Function f = [](double x) { return x * x; };

    double result = simpsonNonRecursive(f, 2, 10, 1000);
    std::cout << "Integral: " << result << std::endl;
    std::cout << "Exact: " << (1000 - 2 * 2 * 2) / 3.0 << std::endl;

    return 0;
}
//----------------------------------------------------------------------