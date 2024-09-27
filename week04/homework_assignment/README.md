# Homework 04: Polymorphism and Root-Finding Algorithms

## Overview

This project implements two numerical root-finding algorithms, **Newton's Method** and the **Secant Method**, using polymorphism and templates in C++. The calculations are executed in both 32-bit (`float`) and 64-bit (`double`) precision using the generic type `T`. The task applies these methods to three different functions, analyzing performance and accuracy.

### Objectives

1. Implement templated base and derived classes to solve for the roots of functions.
2. Apply both Newton's Method and the Secant Method to three different functions.
3. Implement solutions for both `float` and `double` precision.
4. Use smart pointers to manage memory in an alternative version of the project.
5. Verify the root-finding solutions using a custom `verify()` method.
6. Produce plots of the results, including function graphs and error vs. iteration comparisons.

## Problem Statement

We are tasked with finding the roots of the following functions:

1. \( f(x) = \sin(3x - 2) \)
2. \( f(x) = x^3 - 6x^2 + 11x - 8 \)
3. \( f(x) = \log(x) + x^2 - 3 \)

### Methods

1. **Newton's Method**: Requires the derivative of the function and an initial guess.
2. **Secant Method**: Uses two initial guesses and does not require a derivative.

## Requirements

### Files

- **main.cpp**: Contains the code to solve the root-finding problem for both methods.
- **main1.cpp**: A version of the `main.cpp` that uses smart pointers to avoid memory management issues.
- **solver.h**: Abstract base class `Function` with pure virtual functions for root-finding.
- **newton.h**: Derived class implementing Newton's Method.
- **secant.h**: Derived class implementing the Secant Method.
- **specific_functions.h**: Contains the three target functions as derived classes.
- **Makefile**: Automates compilation, including different targets for main files and precision.
- **README.md**: Report detailing the project.
- **plots/**: Directory containing plots for analysis.

### Dependencies

- C++ compiler (e.g., `g++`)
- Plotting tool (e.g., Python with `matplotlib` or `gnuplot`) to generate graphs of the results.

## Compilation and Execution

### Compile

Use the provided Makefile to compile the code.

```bash
make all
