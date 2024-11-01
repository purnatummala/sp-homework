#include "polynomial.hpp"
#include <iostream>
#include <vector>

int main() {
    try {
        // Test case 1: 
        std::vector<double> zeros1 = {-0.86, -0.34,0.34, 0.86};
        PolynomialBinaryTree::saveEvaluations(zeros1, "polynomial_evaluation1.txt");
        std::cout << "Generated evaluation file for first set of zeros\n";

        // Test case 2: 
        std::vector<double> zeros2 = {-0.90, -0.54, 0.0, 0.54, 0.90};
        PolynomialBinaryTree::saveEvaluations(zeros2, "polynomial_evaluation2.txt");
        std::cout << "Generated evaluation file for second set of zeros\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}