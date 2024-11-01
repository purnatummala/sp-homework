#include "polynomial.hpp"
#include <iostream>
#include <vector>

int main() {
    try {
        // Test case 1: zeros = {-0.5, 0, 0.5}
        std::vector<double> zeros1 = {-0.5, 0.0, 0.5};
        PolynomialBinaryTree::saveEvaluations(zeros1, "polynomial_evaluation1.txt");
        std::cout << "Generated evaluation file for first set of zeros\n";

        // Test case 2: zeros = {-1, -0.5, 0, 0.5, 1}
        std::vector<double> zeros2 = {-1.0, -0.5, 0.0, 0.5, 1.0};
        PolynomialBinaryTree::saveEvaluations(zeros2, "polynomial_evaluation2.txt");
        std::cout << "Generated evaluation file for second set of zeros\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}