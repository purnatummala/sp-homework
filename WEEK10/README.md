# Parallel and Adaptive Trapezoidal Integration: Report and Conclusions

## **Part 5: Report and Conclusions**

### **1. Summary of Results for All Tested Configurations**

#### **1.1 Execution Time, Function Evaluations, and Load Balancing Metrics**

The results of the experiments were visualized using different plots for both the **adaptive** and **non-adaptive** trapezoidal methods:

- **Execution Time vs. Number of Threads**:
  - Plots were generated to observe how execution time varied with the number of threads (`t = 1, 2, 4, 8, 16`) for both adaptive and non-adaptive methods.

- **Mean and Standard Deviation of Function Evaluations vs. Number of Threads**:
  - For the **adaptive method**, we plotted **mean function evaluations** and **standard deviation** against the number of threads to analyze **load balancing**.
  - For the **non-adaptive method**, similar plots were generated to validate even distribution of work.

- **Load Balancing Metrics**:
  - For the adaptive method, we plotted **mean time per thread** and **standard deviation** to evaluate workload distribution across threads.

#### **1.2 Error Analysis for Adaptive Methods**

The **error analysis** compared the results between the **parallel** and **sequential** implementations of the adaptive trapezoidal method for different **tolerances** (`1e-3`, `1e-6`):

- The error was quantified as \( |I_{\text{parallel}} - I_{\text{sequential}}| \).
- Plots were generated for **error vs. tolerance** to analyze how reducing tolerance impacts numerical accuracy.

### **2. Interpretation of Results**

To provide insights into the observed trends, we posed a series of questions and answered them using the experimental data and visualizations.

**Q1: How does execution time change as the number of threads (`t`) increases?**
- **Answer**: Execution time decreased with an increasing number of threads, showing improved performance due to parallelization. However, for larger thread counts (`t = 16`), **diminishing returns** were observed due to the overhead of managing multiple threads and increased synchronization costs.

**Q2: How well are workloads balanced in the adaptive method?**
- **Answer**: Analysis of the **mean execution time per thread** and its **standard deviation** indicated that the **adaptive method** suffered from **load imbalances** as the number of threads increased. Some threads finished early, leading to idle time, especially when different subintervals required different levels of subdivision.

**Q3: How does the standard deviation of function evaluations change with the number of threads?**
- **Answer**: In the **adaptive method**, the **standard deviation** of function evaluations increased with more threads, indicating that some threads were handling significantly more subintervals. In contrast, the **non-adaptive method** showed almost zero standard deviation, confirming evenly distributed workloads.

**Q4: How does the error between sequential and parallel results change with tolerance?**
- **Answer**: As the **tolerance** was reduced (e.g., from `1e-3` to `1e-6`), the **error** between parallel and sequential results also decreased, indicating that the parallel implementation converged towards the sequential result with increased precision.

**Q5: Does increasing the number of threads always improve performance for different tolerances and problem sizes?**
- **Answer**: Increasing the number of threads initially led to reduced execution times. However, for **small problem sizes** (`n = 1000`), the overhead of managing multiple threads outweighed the benefit, especially for higher thread counts (`t = 16`). This highlights the **inefficiency of threading** when there is insufficient workload to distribute.

### **3. Conclusions**

#### **3.1 Accuracy vs. Efficiency Trade-Offs**
- **Adaptive Integration**:
  - With lower tolerances, the **adaptive method** provides highly accurate results, but at the cost of increased **execution time**.
  - Parallelization helps reduce execution time but introduces **load balancing challenges** due to dynamic workload subdivision.

- **Non-Adaptive Integration**:
  - In the **non-adaptive method**, workloads are evenly distributed, ensuring balanced **execution times** across threads.
  - Accuracy improves by increasing the number of subintervals (`n`). However, this results in a **linear increase in computation time**.

#### **3.2 Relationship Between Problem Size, Tolerance, and Threading Performance**
- **Problem Size (`n`)**:
  - For **large values of `n`** (e.g., `n = 100,000`), parallelization yields significant performance gains as threads are fully utilized, and the impact of overhead is minimized.
  - For **small values of `n`**, threading overhead becomes prominent, especially for higher numbers of threads (`t = 16`), resulting in reduced performance gains.

- **Tolerance**:
  - In the **adaptive method**, lower tolerance values (`1e-6`) result in a greater number of subintervals, increasing the workload.
  - When using multiple threads, the efficiency decreases for low tolerances due to **uneven work distribution**, leading to **idle threads** and suboptimal performance.

#### **3.3 Recommendations for Efficient Use of Parallel Integration**
- For **non-adaptive integration**, increase `n` and use moderate thread counts (`t <= 8`) to balance accuracy and efficiency.
- For **adaptive integration**, select the number of threads based on the **tolerance** value and **expected workload**. Consider using **work-stealing strategies** to improve load balancing and prevent idle threads.

### **4. Summary**
- **Performance Improvement**: Increasing the number of threads reduces execution time, but gains diminish with larger thread counts due to threading overhead.
- **Load Balancing**: The **adaptive method** faces challenges in workload distribution, particularly with dynamic subdivisions.
- **Error Analysis**: Decreasing tolerance reduces the error between **parallel and sequential** implementations, indicating convergence.
- **Conclusions**:
  - There is a trade-off between **accuracy and efficiency**, especially in adaptive methods where work is distributed dynamically.
  - Careful selection of **problem size**, **tolerance**, and **number of threads** is required to achieve an optimal balance between **performance and accuracy**.

---

### **Plots**
The following plots were generated as part of the analysis:

1. **Execution Time vs. Number of Threads** for Adaptive and Non-Adaptive Methods.
2. **Mean and Standard Deviation of Function Evaluations** for Adaptive and Non-Adaptive Methods.
3. **Load Balancing Analysis**: Mean and Standard Deviation of Execution Time per Thread for the Adaptive Method.
4. **Error vs. Tolerance** for Adaptive Method to show accuracy improvement.

For more details on how to reproduce these plots, refer to the `performance_analysis.py` script in the project repository.

### **How to Reproduce the Analysis**
- Run the `adaptive_trapezoidal` and `non_adaptive_trapezoidal` programs to generate the CSV files.
- Use the provided Python script (`performance_analysis.py`) to generate the plots and analyze the results.

### **Files Included**
- `adaptive_trapezoidal.cpp`: Adaptive trapezoidal integration with parallelization.
- `non_adaptive_trapezoidal.cpp`: Non-adaptive trapezoidal integration with parallelization.
- `performance_analysis.py`: Python script for data visualization and analysis.
- `README.md`: Report and Conclusions.

---

Thank you for your interest in this project. Please feel free to reach out for further clarifications or questions.

