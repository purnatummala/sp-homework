#include <functional>
#include <iostream>
#include <vector>
#include <cmath>  // For std::fabs

using Function = std::function<double(double)>;

struct Interval
{
    double a, b;
    double fa, fb, fm; // Added fm for midpoint
    double area;
    int depth;
};

// Adaptive Simpson Non-Recursive Integration
double adaptiveSimpsonNonRecursive(const Function &f, double a, double b, double tolerance, int maxDepth)
{
    std::vector<Interval> intervals;
    double total_area = 0.0;

    // Initial interval
    double fa = f(a);
    double fb = f(b);
    double mid = (a + b) / 2;
    double fm = f(mid);

    Interval initial;
    initial.a = a;
    initial.b = b;
    initial.fa = fa;
    initial.fb = fb;
    initial.fm = fm;
    initial.area = (b - a) * (fa + 4 * fm + fb) / 6;
    initial.depth = 0;

    intervals.push_back(initial);

    while (!intervals.empty())
    {
        Interval interval = intervals.back();
        intervals.pop_back();

        if (interval.depth >= maxDepth)
        {
            total_area += interval.area;
            continue;
        }

        double c = (interval.a + interval.b) / 2;
        double fc = f(c);

        double left_mid = (interval.a + c) / 2;
        double right_mid = (c + interval.b) / 2;
        double flm = f(left_mid);
        double frm = f(right_mid);

        Interval left, right;
        left.a = interval.a;
        left.b = c;
        left.fa = interval.fa;
        left.fb = fc;
        left.fm = flm;
        left.area = (c - interval.a) * (interval.fa + 4 * flm + fc) / 6;
        left.depth = interval.depth + 1;

        right.a = c;
        right.b = interval.b;
        right.fa = fc;
        right.fb = interval.fb;
        right.fm = frm;
        right.area = (interval.b - c) * (fc + 4 * frm + interval.fb) / 6;
        right.depth = interval.depth + 1;

        double error = std::fabs(left.area + right.area - interval.area);

        if (error < tolerance)
        {
            total_area += left.area + right.area;
        }
        else
        {
            intervals.push_back(right);
            intervals.push_back(left);
        }
    }

    return total_area;
}

//----------------------------------------------------------------------

int main()
{
    const Function f = [](double x) { return x * x; };

    double result = adaptiveSimpsonNonRecursive(f, 2.0, 10.0, 1.e-7, 5);
    std::cout << "Integral: " << result << std::endl;
    std::cout << "Exact: " << (1000 - 2 * 2 * 2) / 3.0 << std::endl;

    return 0;
}
//----------------------------------------------------------------------
