#ifndef SECANT_H
#define SECANT_H

#include "solver.h"
#include "function.h"
#include <cmath>
#include <stdexcept>

template <typename T>
class Secant : public Solver<T> {
public:
    Secant(T tolerance_, int maxIterations_) : Solver<T>(tolerance_, maxIterations_) {}

    T computeRoot(Function<T> &func, T x0, T x1) {
        this->iterationData.clear();
        T f0 = func.f(x0);
        T f1 = func.f(x1);
        for (int i = 0; i < this->maxIterations; ++i) {
            if (std::fabs(f1) < this->tolerance) {
                this->addIterationData(x1);
                return x1;
            }
            T x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
            x0 = x1;
            f0 = f1;
            x1 = x2;
            f1 = func.f(x1);
            this->addIterationData(x1);
        }
        throw std::runtime_error("Max iterations exceeded");
    }

    T computeRoot(Function<T> &func, T x0) override {
        throw std::runtime_error("Secant method requires two initial guesses");
    }
};

#endif