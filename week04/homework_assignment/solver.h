#ifndef SOLVER_H
#define SOLVER_H

#include "function.h"
#include <vector>

template <typename T>
class Solver {
public:
    Solver(T tolerance_, int maxIterations_) : tolerance(tolerance_), maxIterations(maxIterations_) {}

    virtual ~Solver() = default;

    virtual T computeRoot(Function<T> &func, T x0) = 0;

    const std::vector<T>& getIterationData() const {
        return iterationData;
    }

protected:
    void addIterationData(T data) {
        iterationData.push_back(data);
    }

    T tolerance;
    int maxIterations;
    std::vector<T> iterationData;
};

#endif