### Assignment: Adaptive Numerical Integration in C++ with Performance Analysis and Operator Overloading

This revised assignment focuses on building an efficient numerical integration library with timing, function evaluation counting, and benchmarking capabilities. In this version, students will also implement operator overloading to allow integration methods to be chained together across different intervals and methods, providing additional flexibility.

#### Provided Code

The assignment provides pre-implemented functions for core integration algorithms:
```text
- simpson_adaptive_nonrecursive.cpp
- simpson_adaptive_recursive.cpp
- simpson_nonadaptive_nonrecursive.cpp
- simpson_nonadaptive_recursive.cpp
- trapezoidal_adaptive_nonrecursive.cpp
- trapezoidal_adaptive_recursive.cpp
- trapezoidal_nonadaptive_nonrecursive.cpp
- trapezoidal_nonadaptive_recursive.cpp
```

These routines have been debugged (if a bug is found, please report it and we will fix it for you and provide the fix to all the students).

The focus of the assignment is on building a flexible, object-oriented interface around these methods with support for caching of function evaluation, timing of integration methods, 
benchmarking different functions and integration methods, and operator overloading. Benchmarking results will be output to a csv file (comma-separated values) and visualized with Python using either the Seaborn or Matplotlib libraries. 

All code will be written in modern C++ with type-safety in mind. This means you will use the STL library as much as possible. 
Use <algorithms>, `std::function`, `<cmath>` and other "safe" libraries. Use documentation and AI as need to learn about anything you either forgot or 
have difficulty with. 

---

### Task 1: Base Class with Timing and Function Evaluation Caching

#### Objective:

Create a base class for integration methods that supports timing and tracks the number of function evaluations.

#### Instructions:

1. Use the classes `Function`, `CachedFunction` or `FastCachedFunction` in `definitions.h` as a wrapper around a mathematical function, 
tracking the number of evaluations. You will need all three for the benchmarks. 
2. Create an abstract base class `Integration`:
   - Include protected members `a`, `b` (doubles, integration bounds), `isRecursive` (bool), and `isAdaptive` (whether or not the integration mehtod is adaptive), and  a variable that measures the time it takes to integrate the function, measured in seconds.
   - Add a pure method, named `integrate` that actually integrates the functions, which is overridden in the derived classes. . 
   - Add a method to measure execution time and track function evaluations, implemented in the `operator()`, which calls `integrate`. Note
     that the `operator()` function is implemented in the `Integrate` class. 
   - Create two classes: `NonAdaptiveIntegration` and `AdaptiveIntegration`, that derive from the `Integreation` class. The constructor
     arguments will include the integration bounds, whether or not the integration scheme is recursive, and the desired number of intervals. 
     The Adaptive class constructor arguments will also include an absolute error tolerance, whether the scheme is recursive, and the 
     maximum adaptation depth. (look at the provided implementations to better understand.)
   - During the development of your code, add additional functionality to these classes as needed, but avoid as much as possible needless
     duplication (which complicates code maintenance and code extensibility). 

#### Comprehension Questions:

1. How does timing in the base class ensure consistent performance measurement across methods?
2. Why might function evaluation counts vary for the same integration bounds? (look up the different techniques via web search or 
   look at the provided functions that implement these methods.)
3. What are the implementation differences between the classes `CachedFunction` and `FastCachedFunction`? What is the asymptotic complexity of each? In other words, what is the average computational required to identify whether a function has already been evaluated? 
4. What is the new issue to consider when caching functions evaluated at values of `x` that are `doubles` rather than `int`? How was this issue addressed in the implementations provided? 

---

### Task 2: Derived Integration Classes Using Provided Functions

#### Objective:

Implement derived classes for Trapezoidal and Simpson’s methods (both basic and adaptive) using the provided integration functions.

#### Instructions:

1. Create `Trapezoidal` and `Simpson` classes that inherit from `IntegrationMethod`.
2. Implement the `integrate` function in each class by using the corresponding provided function.
3. For adaptive integration, create `AdaptiveTrapezoidal` and `AdaptiveSimpson`, using the respective adaptive functions and ensuring they respect the `tolerance` parameter.
4. In total, you'll have 8 integration schemes available to you. 

#### Comprehension Questions:

1. How does polymorphism simplify the integration library’s design?
2. What is the purpose of depth control in adaptive methods?

---

### Task 3: Overloading the Addition Operator for Integration Chaining

#### Objective:

Implement operator overloading for `+` to allow chaining of `IntegrationMethod` objects over adjacent intervals.

#### Instructions:

1. Overload the `+` operator in `IntegrationMethod` to allow integration methods with adjacent intervals to be combined. The overloaded operator should:
   - Check that intervals are contiguous, i.e., `b` of the left operand equals `a` of the right operand.
   - Return the sum of the results of the individual integrations.
   - Include exception handling to make sure that  only valid integrations can be summed. 

    ```cpp
    double operator+(Integration &lhs, Integration &rhs) {
       /* Add your own implementation */
      return /* the sum of the two integrands */ ...
    }
    ```

2. Modify `main.cpp` to demonstrate chaining multiple integrals with different methods over contiguous intervals (e.g., `[a, b] + [b, c] + [c, d]`).

#### Comprehension Questions:

1. Why must intervals be contiguous for the addition operation to make sense?
2. What would happen if two non-contiguous intervals were mistakenly added?

---

### Task 4: Testing and Benchmarking Framework

#### Objective:

Implement a testing and benchmarking framework to measure computational cost and accuracy.

#### Instructions:

1. Define several test functions with known analytical integrals (e.g., `sin(x)`, `log(x)`, `sin(2x)`).
You also have more complex functions provided in `complicated_functions.cpp`. 
2. Write a `benchmarkMethod` function that:
   - Resets the function evaluation count.
   - Empties the cache
   - Uses `operator()` to call each integration method, tracking execution time and function evaluation count.
   - Calculates the absolute error by comparing the numerical result with the analytical solution.
   - For the adaptive methods, use a maximum depth of 12, and a tolerance of 1.e-8.
   - Note: If a function is evaluate twice at `x`, with `x` within some error tolerance, the evaluation count is 1. 
3. Use lambda functions as much as possible. Do not use standard functions as given in `complicated_functions.cpp`

#### Comprehension Questions:

1. How does function evaluation count help measure the efficiency of each method?
2. How does execution time relate to the function complexity and interval size?

---

### Task 5: Performance Analysis Report

#### Objective:

Summarize and analyze the results from the benchmarking framework, focusing on cost, accuracy, and effectiveness of the addition operator.

#### Instructions:

1. Define a structure (or class): `IntegrationResults` to store relevant data from a single function integration, which includes: 
   method name, function name, cache_type (none, fast, slow), nb_intervals or max_depth, recursive (true/false), numerical results returned by the integration method, analytical results (if availalble, else -1), absolute_error (if available, else -1)
1. Based on Task 4, benchmark each integration method with each test function and record performance metrics. Do this for the case with 
   no cache, slow cache, or fast cache. 
2. Analyze results, comparing time and accuracy of each method across different intervals. Do this by outputing a csv file with the results from the integration. 
3. Discuss the effectiveness of the `+` operator for chaining intervals. Time the + operator. 

#### Analysis Questions:

1. Which integration method performed best in terms of accuracy and computational cost?
2. How did the addition operator improve flexibility in chaining multiple intervals?
3. What insights can be drawn from using adaptive vs. non-adaptive methods in different interval configurations?

---

### Grading Rubric

Points | Criterion                    | Excellent (90-100%)                           | Good (70-89%)                              | Satisfactory (50-69%)                        | Needs Improvement (<50%)                        |
|------------------------------|-----------------------------------------------|--------------------------------------------|----------------------------------------------|-------------------------------------------------|
|10%| **Correctness**              | All methods implemented correctly; addition operator works seamlessly for contiguous intervals. | Minor issues in implementation, mostly correct results. | Basic cases correct, some edge cases failing. | Major errors or missing methods, incomplete or incorrect results. |
|10%| **Performance Measurement**  | Efficient timing and function call tracking; accurate reporting across methods. | Mostly accurate tracking, minor inaccuracies. | Basic tracking but lacking in some details. | Poorly implemented tracking, significant inaccuracies. |
|10%| **Operator Overloading**     | Addition operator is implemented correctly, supporting chaining across multiple methods. | Works mostly as intended, some minor issues with chaining. | Works for basic cases, fails in some complex cases. | Addition operator does not work as intended or fails completely. |
|10%| **Code Structure & OOP**     | Code is modular, well-organized, with clear use of polymorphism. | Mostly modular with minor improvements needed. | Some modularity, but limited use of polymorphism. | Minimal OOP use, poorly structured or repetitive code. |
|10%| **Documentation & Clarity**  | Code is well-documented, with clear logic and readability. | Mostly clear, with some documentation gaps. | Limited documentation, somewhat readable. | Lacks documentation, difficult to understand. |
|10%| **Analysis & Insight**       | Thorough benchmark analysis with clear insights on cost, accuracy, and addition operator benefits. | Some analysis, with partial insights. | Minimal analysis, limited interpretation of results. | Lacks meaningful analysis, results not interpreted. |
|10%| **Design Decisions**  | Thoroughly justified architectural choices with clear understanding of tradeoffs | Good justification of major decisions | Basic explanation of choices | Limited or no justification |
|10%| **Analysis Depth**  | Comprehensive analysis of performance, stability, and design implications | Good analysis with some gaps | Basic analysis of results | Superficial analysis |
|10%| **Implementation Understanding**  | Clear demonstration of deep understanding through unique optimizations and design choices | Good understanding shown in implementation | Basic implementation with limited insight | Implementation shows lack of understanding |

---

### Grading Notes:

- **Correctness**: Confirm all integration methods are implemented correctly and the addition operator works as intended.
- **Operator Overloading**: Emphasize operator functionality for chaining integration intervals.
- **Performance Measurement**: Evaluate the accuracy of timing and function evaluation counts.
- **Documentation**: Encourage comments on key sections, especially for operator overloading logic.
- **Insight**: Benchmark analysis should reveal trade-offs between function calls, execution time, error, and addition operator benefits.

### Additional Notes: 

- Implement your framework with a single function for which you know the analytical answer. 
- Once your code works with a single function, add the other functions into a vector and run all the tests. 
- Provide your code in your github repository
- Generate a pdf report left in your repository and uploaded to Canvas
- Document all functions
- In your report: 
  - Justify any decisions you make, especially when you are having to choose between multiple options
  - Use a python program to plot data collected in your csv file. You will make your own decisions as to what 
    data to plot and how to plot it. Provide explanations about what you learned from your plots. Every plot you choose
    must have a corresponding description and statement about what you learned from it. 
    You can plot cost, execution time, compare function characteristics, you can add your own functions to demonstrate specific
    issues. 
  - Indicate how you tested whether your implements were correct? 
  - Include a Makefile. You can  generate multiple targets. I recommend that the benchmarks that generate the csv file be placed in a separate file, `benchmark_main.cpp`. 
    In this case, your targets are `main.x` and `benchmark_main.x`. 
  - Use Modern C++ to code. Use STL and std:: as much as possible. 
  - Math operators use std:: for safety and are defined in `<cmath>`


