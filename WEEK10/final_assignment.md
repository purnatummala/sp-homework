### **Comprehensive Threading Assignment: Parallel Numerical Integration**

---

#### **Theme:** Optimizing Numerical Integration with Adaptive Methods and Threading

This assignment builds on provided sequential implementations of recursive and non-recursive trapezoidal integration (adaptive and non-adaptive). Your task is to parallelize these methods using modern C++, analyze their performance, and evaluate their scalability.

---

### **Instructions**
1. **Starting Point:** Use the provided sequential implementations as a basis for your work.
2. **Submission:** Your submission must include:
    - A **repository** with your code, a **Makefile**, and a **report** in PDF format uploaded to Canvas.
3. **Language:** Use modern C++ (C++17 or later), and implement functions using `std::function` and/or lambda functions.
4. **Thread-Safety:** Your code must be thread-safe. Research and implement best practices for thread safety, such as mutexes or atomic operations.
5. **Focus:** Track key performance metrics such as function evaluations, load balancing, and execution time.

---

### **Assignment Parts**

#### **Part 1: Parallel Non-Adaptive Trapezoidal Integration**
- **Goal:** Parallelize the provided non-adaptive trapezoidal integration method.
- **Task:**
    1. Use threads to compute subinterval integrals concurrently.
    2. Implement work distribution such that intervals are evenly divided among threads.
    3. Test on:
     $$f(x) = x^3 - 3x^2 + 2$$
     over $[0, 2]$ with $n = 10^3, 10^4, 10^5$ using thread counts $t = 1, 2, 4, 8, 16$.
    4. Measure and report:
        - Total execution time for each configuration.
        - Number of function evaluations per thread.
    5. Analyze load balancing by calculating:
        - Mean and standard deviation of function evaluations per thread.
        - Mean and standard deviation of thread execution times.

---

#### **Part 2: Parallel Adaptive Trapezoidal Integration**
- **Goal:** Parallelize the provided adaptive trapezoidal method.
- **Task:**
    1. Implement a parallel version of the adaptive method using threads, ensuring thread safety.
    2. Use a thread pool to manage concurrency efficiently.
    3. Assign subintervals dynamically to threads, considering that different intervals may require varying numbers of function evaluations.
    4. Test on:
     $$f(x) = \sqrt{x}(1 - x)^2$$
     over $[0, 1]$ with tolerances $\epsilon = 10^{-3}, 10^{-6}$ using thread counts $t = 1, 2, 4, 8, 16$.
    5. Measure and report:
        - Total execution time for each configuration.
        - Number of function evaluations performed by each thread.
    6. Analyze:
        - Load balancing (mean and standard deviation of function evaluations across threads).
        - Thread execution times (mean and standard deviation).

---

#### **Part 3: Performance Analysis and Scalability**
- **Goal:** Analyze performance trends for non-adaptive and adaptive methods.
- **Task:**
    1. Generate plots for each method:
        - Execution time vs. number of threads ($t = 1, 2, 4, 8, 16$).
        - Mean and standard deviation of function evaluations vs. number of threads.
    2. Analyze the following dimensions:
        - **Scalability:** How does performance improve with increasing threads? Identify diminishing returns and explain why they occur.
        - **Load Balancing:** Discuss the relationship between the number of threads and the distribution of work. What factors lead to imbalances in adaptive methods?
        - **Overhead:** Compare adaptive and non-adaptive methods. How does the cost of managing threads and work allocation impact performance?

---

#### **Part 4: Validity and Robustness**
- **Goal:** Ensure correctness and robustness of parallel implementations.
- **Task:**
    1. Verify the results of your parallel implementations against the provided sequential versions:
        - Use analytical solutions or a high-precision sequential implementation for reference.
        - Quantify numerical errors as $|I_{\text{parallel}} - I_{\text{sequential}}|$.
    2. Discuss how to ensure thread safety and validate your implementation.
    3. Address:
        - What tests can you perform to validate correctness?
        - What are common pitfalls in parallel numerical integration?

---

#### **Part 5: Report and Conclusions**
- **Goal:** Synthesize your findings in a structured report.
- **Task:**
    1. Summarize results for all tested configurations, including:
        - Plots of execution time, function evaluations, and load balancing metrics.
        - Error analysis for adaptive methods with different tolerances.
    2. Interpret the results obtained in the experiments
        - Pose a series (up to 5) of questions and answer them with support from your data and visualizations
    3. Provide clear conclusions addressing:
        - Accuracy and efficiency trade-offs.
        - The relationship between problem size, tolerance, and threading performance.

---

### **Rubric**

| Task                                      | Points | Criteria                                                                                              |
|-------------------------------------------|--------|-------------------------------------------------------------------------------------------------------|
| Part 1: Parallel Non-Adaptive             | 15     | Correct implementation, efficient threading, and clear performance metrics.                           |
| Part 2: Parallel Adaptive                 | 25     | Proper parallelization, thread safety, and dynamic work distribution.                                 |
| Part 3: Performance Analysis and Scalability | 20     | Meaningful plots, insightful discussion of scalability, load balancing, and overhead.                  |
| Part 4: Validity and Robustness           | 20     | Accurate validation, thoughtful error analysis, and robust thread-safe implementation.                |
| Part 5: Report and Conclusions            | 20     | Clear, well-structured report with supported conclusions and meaningful insights.                     |
| Edge Cases (Bonus points)                 | 10     | Thorough testing of edge cases, including analysis of results and handling of challenging scenarios.   |
| **Total**                                 | 100    |                                                                                                       |

---

### **Edge Cases (10 Points)**
Incorporate edge cases as an additional task. Evaluate correctness and performance for functions that introduce challenging behaviors, such as:
1. **Oscillatory Function:**
   $$f(x) = \sin\left(\frac{1}{x + 0.01}\right)$$ over \([0, 1]\).
2. **Localized Spike:**
   $$f(x) = e^{-\frac{(x - 0.5)^2}{0.01}}$$ over \([0, 1]\).

For these functions:
- Validate results with a high-precision sequential implementation. Use the [Python module](https://docs.scipy.org/doc/scipy/tutorial/integrate.html) 
 `scipy.integrate` . Describe how you performed the accuracy verification. 
- Analyze how adaptivity and threading handle challenging regions.
- Discuss observed errors and performance metrics.

This rubric update ensures comprehensive evaluation and prioritizes the inclusion of edge-case testing as a critical skill.

---

### **Submission Requirements**
1. **Code Repository:** Include:
    - Source code implementing parallel non-adaptive and adaptive methods.
    - A `Makefile` for building your code.
2. **Plots and Results:** Include in the report:
    - Execution time vs. threads.
    - Mean and standard deviation of function evaluations and execution times.
    - Error analysis plots.
3. **Report:** Submit a PDF containing:
    - Description of your implementation.
    - Answers to all posed questions. Copy each question into your report and then answer it. Make your report clear for easy grading. 
    - Charts and tables summarizing your findings.
4. **Thread Safety Documentation:** Highlight steps taken to ensure thread-safe execution. (look this up if you want more information). 

---

### **Key Notes**
- Use `std::function` or lambda functions for all integrand definitions.
- Implement thread-safe techniques using mutexes, condition variables, or atomic operations where needed.
- Manage threads efficiently, minimizing overhead from thread creation and synchronization.
- Test your implementations rigorously on edge cases to ensure correctness and robustness.
- Use `<chrono>` for all timings. Feel free to create your own methods to make implementation easier. These helper 
  functions can be stored in a file `utils.h` and `utils.cpp` (if necessary). 

This assignment challenges your understanding of threading, numerical integration, and performance optimization. Good luck!
