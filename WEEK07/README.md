# Polynomial Binary Tree Library Documentation

## Overview
This library provides a flexible and powerful system for creating, manipulating, and analyzing polynomials using a binary tree representation. The implementation supports polynomial generation from zeros, differentiation, evaluation, and visualization.

## Key Components

### 1. Node Class
The `Node` class represents individual elements in the polynomial's binary tree structure.

#### Node Types
- `CONSTANT`: Represents numeric values
- `VARIABLE`: Represents the variable (x)
- `OPERATOR`: Represents mathematical operations (+, -, *)

#### Node Attributes
- `type`: The type of the node (NodeType enum)
- `value`: Numeric value for constants
- `variable`: Character representing the variable
- `op`: Operator character
- `left` and `right`: Child nodes for complex expressions

### 2. PolynomialBinaryTree Class
The main class for polynomial manipulation.

#### Key Methods

##### `fromZeros(zeros)`
- **Purpose**: Creates a polynomial from a list of zeros
- **Input**: Vector of zeros (roots of the polynomial)
- **Process**: 
  1. Starts with (x - first_zero)
  2. Multiplies successive (x - zero) terms
- **Example**: 
  - Zeros [-0.5, 0, 0.5] creates the polynomial: (x+0.5)(x)(x-0.5)

##### `differentiate()`
- **Purpose**: Computes the derivative of the polynomial
- **Implementation**: Uses the chain rule and product rule
- **Supports derivatives for constants, variables, and compound expressions**

##### `evaluate(x)`
- **Purpose**: Calculates the polynomial's value for a given x
- **Recursively traverses the binary tree**

##### `saveEvaluations(zeros, filename)`
- **Purpose**: Generate comprehensive polynomial evaluation data
- **Features**:
  - Computes the original polynomial and its first 5 derivatives
  - Saves evaluations across a specified range
  - Outputs a tab-separated file with x and derivative values

## Usage Example

```cpp
// Create a polynomial with zeros {-0.86, -0.34,0.34, 0.86}
std::vector<double> zeros = {-0.86, -0.34,0.34, 0.86};
PolynomialBinaryTree poly = PolynomialBinaryTree::fromZeros(zeros);

// Evaluate the polynomial at x = 1
double value = poly.evaluate(1.0);

// Get the first derivative
PolynomialBinaryTree derivative = poly.differentiate();
```

## Visualization
The accompanying Python script (`plot_polynomials.py`) provides visualization capabilities:
- Generates plots of the polynomial and its derivatives
- Highlights zero points
- Creates high-resolution PDF outputs

## Key Design Principles
- **Flexible Tree Representation**: Allows complex polynomial expressions
- **Recursive Operations**: Differentation and evaluation use recursive tree traversal
- **Error Handling**: Throws exceptions for invalid inputs
- **Memory Management**: Uses smart pointers for safe memory handling

## Limitations and Considerations
- Currently supports basic operations (+, -, *)
- Handles only single-variable polynomials
- Computational complexity increases with polynomial complexity

## Potential Improvements
- Add support for more complex operations (division, power)
- Implement symbolic manipulation
- Enhance error checking and validation

## Performance Notes
- Tree-based representation provides flexibility
- Recursive operations may have higher computational overhead compared to direct polynomial representations
