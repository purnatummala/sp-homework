#include "solver.h"
#include "function.h"
#include "newton.h"
#include "secant.h"
#include "specific_functions.h"
#include <memory>
#include <fstream>
#include <iostream>

int main() {
    std::vector<std::unique_ptr<Function<double>>> functions;
    functions.push_back(std::make_unique<SinFunction<double>>());
    functions.push_back(std::make_unique<PolynomialFunction<double>>());
    functions.push_back(std::make_unique<LogFunction<double>>());

    struct SolverParams {
        double tolerance;
        int maxIterations;
        double initialGuessNewton;
        double initialGuessSecant1;
        double initialGuessSecant2;
    };

    std::vector<SolverParams> params = {
        {0.01, 100, 1.0, 1.0, 2.0},
        {0.001, 500, 1.0, 1.0, 2.0},
        {0.0001, 1000, 1.0, 1.0, 2.0},
        {0.00001, 2000, 1.0, 1.0, 2.0},
        {0.000001, 5000, 1.0, 1.0, 2.0},
        {0.0000001, 20000, 1.0, 1.0, 2.0}  // Increased max iterations
    };

    std::ofstream newtonFile("newton_iterations.csv");
    std::ofstream secantFile("secant_iterations.csv");

    for (const auto& func : functions) {
        for (const auto& p : params) {
            try {
                auto newtonSolver = std::make_unique<Newton<double>>(p.tolerance, p.maxIterations);
                double newtonRoot = newtonSolver->computeRoot(*func, p.initialGuessNewton);
                std::cout << func->name() << " (Newton): " << newtonRoot << std::endl;
                const auto& newtonRoots = newtonSolver->getIterationData();
                for (size_t i = 0; i < newtonRoots.size(); ++i) {
                    newtonFile << i + 1 << "," << newtonRoots[i] << "\n";
                }
            } catch (const std::runtime_error& e) {
                std::cerr << func->name() << " (Newton): " << e.what() << std::endl;
            }

            try {
                auto secantSolver = std::make_unique<Secant<double>>(p.tolerance, p.maxIterations);
                double secantRoot;
                if (func->name() == "x^3 - 6x^2 + 11x - 8") {
                    // Adjust initial guesses for the polynomial function
                    secantRoot = secantSolver->computeRoot(*func, 2.5, 3.5);
                } else {
                    secantRoot = secantSolver->computeRoot(*func, p.initialGuessSecant1, p.initialGuessSecant2);
                }
                std::cout << func->name() << " (Secant): " << secantRoot << std::endl;
                const auto& secantRoots = secantSolver->getIterationData();
                for (size_t i = 0; i < secantRoots.size(); ++i) {
                    secantFile << i + 1 << "," << secantRoots[i] << "\n";
                }
            } catch (const std::runtime_error& e) {
                std::cerr << func->name() << " (Secant): " << e.what() << std::endl;
            }
        }
    }

    newtonFile.close();
    secantFile.close();

    return 0;
}