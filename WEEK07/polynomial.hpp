#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <memory>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdexcept>

// Node types enumeration
enum class NodeType {
    CONSTANT,
    VARIABLE,
    OPERATOR
};

// Node class for polynomial terms
class Node {
public:
    NodeType type;
    double value;           // For constants
    char variable;          // For variables
    char op;               // For operators
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    // Constructors for different node types
    Node(double val) : type(NodeType::CONSTANT), value(val), variable('\0'), op('\0') {}
    Node(char var) : type(NodeType::VARIABLE), value(0), variable(var), op('\0') {}
    Node(char operation, std::shared_ptr<Node> l, std::shared_ptr<Node> right)
        : type(NodeType::OPERATOR), value(0), variable('\0'), op(operation), 
          left(std::move(l)), right(std::move(right)) {}
};

class PolynomialBinaryTree {
private:
    std::shared_ptr<Node> root;

    // Helper method for differentiation - now marked as const
    std::shared_ptr<Node> differentiateNode(const std::shared_ptr<Node>& node) const;
    
    // Helper method for evaluation
    double evaluateNode(const std::shared_ptr<Node>& node, double x) const;

public:
    PolynomialBinaryTree() : root(nullptr) {}

    // Create polynomial from zeros
    static PolynomialBinaryTree fromZeros(const std::vector<double>& zeros);

    // Differentiation
    PolynomialBinaryTree differentiate() const;

    // Evaluation
    double evaluate(double x) const;

    // Save polynomial and derivatives evaluation to file
    static void saveEvaluations(const std::vector<double>& zeros, 
                              const std::string& filename,
                              double start = -1.0,
                              double end = 1.0,
                              int points = 100);
};

#endif // POLYNOMIAL_HPP