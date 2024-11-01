#include "polynomial.hpp"

std::shared_ptr<Node> PolynomialBinaryTree::differentiateNode(const std::shared_ptr<Node>& node) const {
    if (!node) return nullptr;

    switch (node->type) {
        case NodeType::CONSTANT:
            return std::make_shared<Node>(0.0);
        case NodeType::VARIABLE:
            return std::make_shared<Node>(1.0);
        case NodeType::OPERATOR: {
            if (node->op == '+' || node->op == '-') {
                return std::make_shared<Node>(node->op,
                    differentiateNode(node->left),
                    differentiateNode(node->right));
            } else if (node->op == '*') {
                // Product rule: d(u*v) = u'v + uv'
                auto leftTerm = std::make_shared<Node>('*',
                    differentiateNode(node->left),
                    std::make_shared<Node>(*node->right));  // Make a copy
                auto rightTerm = std::make_shared<Node>('*',
                    std::make_shared<Node>(*node->left),    // Make a copy
                    differentiateNode(node->right));
                return std::make_shared<Node>('+', leftTerm, rightTerm);
            }
        }
    }
    return nullptr;
}

double PolynomialBinaryTree::evaluateNode(const std::shared_ptr<Node>& node, double x) const {
    if (!node) return 0.0;

    switch (node->type) {
        case NodeType::CONSTANT:
            return node->value;
        case NodeType::VARIABLE:
            return x;
        case NodeType::OPERATOR:
            switch (node->op) {
                case '+': return evaluateNode(node->left, x) + evaluateNode(node->right, x);
                case '-': return evaluateNode(node->left, x) - evaluateNode(node->right, x);
                case '*': return evaluateNode(node->left, x) * evaluateNode(node->right, x);
            }
    }
    return 0.0;
}

PolynomialBinaryTree PolynomialBinaryTree::fromZeros(const std::vector<double>& zeros) {
    if (zeros.empty()) {
        throw std::invalid_argument("Cannot create polynomial from empty zeros list");
    }

    PolynomialBinaryTree result;
    // Start with (x - zeros[0])
    auto term = std::make_shared<Node>('-',
        std::make_shared<Node>('x'),
        std::make_shared<Node>(zeros[0]));
    result.root = term;

    // Multiply by (x - zeros[i]) for each remaining zero
    for (size_t i = 1; i < zeros.size(); ++i) {
        auto newTerm = std::make_shared<Node>('-',
            std::make_shared<Node>('x'),
            std::make_shared<Node>(zeros[i]));
        result.root = std::make_shared<Node>('*', result.root, newTerm);
    }

    return result;
}

PolynomialBinaryTree PolynomialBinaryTree::differentiate() const {
    PolynomialBinaryTree result;
    result.root = differentiateNode(root);
    return result;
}

double PolynomialBinaryTree::evaluate(double x) const {
    return evaluateNode(root, x);
}

void PolynomialBinaryTree::saveEvaluations(const std::vector<double>& zeros, 
                                         const std::string& filename,
                                         double start,
                                         double end,
                                         int points) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    // Create polynomial and its derivatives
    auto poly = PolynomialBinaryTree::fromZeros(zeros);
    std::vector<PolynomialBinaryTree> derivatives;
    derivatives.push_back(poly);
    for (int i = 0; i < 5; ++i) {
        derivatives.push_back(derivatives.back().differentiate());
    }

    // Write header
    file << "x P(x) P'(x) P''(x) P'''(x) P''''(x) P'''''(x)\n";

    // Evaluate at specified points
    double step = (end - start) / (points - 1);
    for (int i = 0; i < points; ++i) {
        double x = start + i * step;
        file << std::fixed << std::setprecision(4) << x;
        for (const auto& deriv : derivatives) {
            file << " " << deriv.evaluate(x);
        }
        file << "\n";
    }
}