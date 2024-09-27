#include "solver.h"
#include "function.h"
#include "newton.h"
#include "secant.h"
#include "specific_functions.h"
#include <memory>
#include <fstream>
#include <iostream>

int main() {
    std::vector<std::unique_ptr<Function<float>>> functions;
    functions.push_back(std::make_unique<SinFunction<float>>());
    functions.push_back(std::make_unique<PolynomialFunction<float>>());
    functions.push_back(std::make_unique<LogFunction<float>>());

    struct SolverParams {
        float tolerance;
        int maxIterations;
    };
    std::vector<SolverParams> params = {
        {0.01f, 100},
        {0.001f, 500},
        {0.0001f, 1000},
        {0.00001f, 2000},
        {0.000001f, 5000},
        {0.0000001f, 10000}
    };

    std::ofstream newtonFile("newton_iterations_float.csv");
    std::ofstream secantFile("secant_iterations_float.csv");

    for (const auto& func : functions) {
        for (const auto& p : params) {
            auto newtonSolver = std::make_unique<Newton<float>>(p.tolerance, p.maxIterations);
            float newtonRoot = newtonSolver->computeRoot(*func, 1.0f);
            std::cout << "Newton's method root: " << newtonRoot << std::endl;
            const auto& newtonRoots = newtonSolver->getIterationData();
            for (size_t i = 0; i < newtonRoots.size(); ++i) {
                newtonFile << i + 1 << "," << newtonRoots[i] << "\n";
            }

            auto secantSolver = std::make_unique<Secant<float>>(p.tolerance, p.maxIterations);
            float secantRoot = secantSolver->computeRoot(*func, 1.0f, 2.0f);
            std::cout << "Secant method root: " << secantRoot << std::endl;
            const auto& secantRoots = secantSolver->getIterationData();
            for (size_t i = 0; i < secantRoots.size(); ++i) {
                secantFile << i + 1 << "," << secantRoots[i] << "\n";
            }
        }
    }

    newtonFile.close();
    secantFile.close();

    return 0;
}