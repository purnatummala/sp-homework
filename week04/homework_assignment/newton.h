#ifndef NEWTON_H
#define NEWTON_H

#include "solver.h"
#include "function.h"
#include <cmath>
#include <stdexcept>

template <typename T>
class Newton : public Solver<T> {
public:
    Newton(T tolerance_, int maxIterations_) : Solver<T>(tolerance_, maxIterations_) {}

    T computeRoot(Function<T> &func, T x0) override {
        this->iterationData.clear();
        for (int i = 0; i < this->maxIterations; ++i) {
            T fx = func.f(x0);
            T dfx = func.df(x0);
            if (std::fabs(fx) < this->tolerance) {
                this->addIterationData(x0);
                return x0;
            }
            x0 = x0 - fx / dfx;
            this->addIterationData(x0);
        }
        throw std::runtime_error("Max iterations exceeded");
    }
};

#endif