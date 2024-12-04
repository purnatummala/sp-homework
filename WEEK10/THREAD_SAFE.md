# Thread Safety Documentation

## **Ensuring Thread-Safe Execution in Adaptive and Non-Adaptive Trapezoidal Integration**

Thread safety is crucial when implementing numerical integration in a parallel environment. Below, we describe how thread safety has been ensured in both the **adaptive** and **non-adaptive trapezoidal integration** methods, detailing the strategies employed to guarantee correct and robust execution.

### **1. Non-Adaptive Trapezoidal Integration**

In the **non-adaptive trapezoidal integration** implementation, the task is divided evenly among threads, and each thread is responsible for a specific set of subintervals.

#### **1.1 Task Assignment and Queue Management**
- **Static Task Assignment**:
  - The **non-adaptive** approach divides the range into a fixed number of subintervals, which are statically assigned to threads.
  - Each thread is assigned its portion of work at the beginning, which ensures **predictable and balanced workloads**.

#### **1.2 Mutex Locks for Shared Resources**
- **Mutex for Result Variable (`std::mutex result_mutex`)**:
  - A **mutex** is used to protect the **result variable** that accumulates results from all threads.
  - This ensures that only one thread can modify the result at any time, preventing inconsistencies due to concurrent writes.

#### **1.3 Thread Safety Mechanisms**
- **Atomic Variables (`std::atomic<int> active_tasks`)**:
  - The **active_tasks** variable keeps track of how many threads are currently processing. This variable is updated using atomic operations to ensure thread safety without requiring additional locks.

#### **1.4 Deadlock Avoidance**
- **Consistent and Minimal Lock Scope**:
  - Locks are always acquired in a consistent order, and they are held for only as long as needed, which helps avoid deadlocks and reduces contention among threads.

#### **1.5 Load Balancing through Static Task Assignment**
- **Even Distribution**:
  - In the **non-adaptive method**, each thread is given an equal number of subintervals, leading to predictable and even workload distribution. This avoids the need for dynamic balancing and ensures efficient utilization of threads.

### **2. Adaptive Trapezoidal Integration**

The **adaptive trapezoidal integration** dynamically subdivides the integration range based on the required tolerance. This introduces challenges in workload distribution, which requires additional considerations for thread safety and efficient execution.

#### **2.1 Task Queue Management**
- **Dynamic Task Queue (`std::queue<Task> tasks`)**:
  - A **task queue** is used to manage the dynamically generated tasks.
  - As the integration proceeds, tasks are subdivided and added back to the queue, which requires careful management to avoid race conditions.

- **Mutex Lock for Queue Access (`std::mutex queue_mutex`)**:
  - A **mutex lock** protects the task queue to ensure that only one thread can add or remove tasks at a time, preventing multiple threads from modifying the queue simultaneously.

#### **2.2 Synchronization with Condition Variables**
- **Condition Variable (`std::condition_variable condition`)**:
  - **Condition variables** are used to synchronize threads and notify them when new tasks are available or when it's time to stop processing.
  - Threads wait on the condition variable to be notified, which ensures efficient use of CPU resources rather than actively polling for tasks.

#### **2.3 Atomic Variables for Shared State Tracking**
- **Atomic Stop Flag (`std::atomic<bool> stop`)**:
  - The **stop** flag ensures that all threads exit once the computation is complete.
  
- **Atomic Task Counter (`std::atomic<int> active_tasks`)**:
  - Keeps track of the number of active tasks in the queue.
  - Atomic operations ensure that the counter is updated safely, without the need for additional locks.

#### **2.4 Result Accumulation with Mutex Protection**
- **Shared Result Variable (`double result`)**:
  - Threads update a shared result variable (`result`) as they complete their subinterval calculations.
  - **Mutex (`std::mutex result_mutex`)** ensures serialized access to this variable, preventing concurrent writes that could lead to data corruption.

#### **2.5 Thread Execution Timing and Evaluation Tracking**
- **Per-Thread Data Tracking**:
  - Each thread maintains its **execution time** (`thread_execution_times`) and **number of function evaluations** (`function_evaluations`).
  - These values are tracked independently for each thread, avoiding the need for locks and ensuring safe access.

#### **2.6 Deadlock Avoidance**
- **Locking Strategy**:
  - The locks for shared resources are always acquired in a consistent order, which prevents circular dependencies.
  - **Minimal Lock Scope** ensures that locks are held only for as long as necessary, reducing contention among threads and avoiding deadlocks.

#### **2.7 Load Balancing Considerations**
- **Dynamic Work Allocation**:
  - Tasks are dynamically enqueued based on the recursive subdivision of integration intervals.
  - Worker threads continuously pick up available tasks, ensuring that all threads are engaged until the work is fully completed.
  - This approach helps in achieving better **load balancing** as compared to the **non-adaptive** method, though imbalances can still occur due to the uneven nature of adaptive subdivisions.

### **3. Summary of Thread Safety Measures for Both Methods**

#### **Non-Adaptive Method**:
- **Static Task Assignment** ensures even workload distribution.
- **Mutex** protects access to the **shared result variable**, ensuring correctness.
- **Atomic variables** are used for shared state tracking.

#### **Adaptive Method**:
- **Task Queue with Mutex** ensures serialized access for dynamically generated tasks.
- **Condition Variables** provide efficient synchronization among threads.
- **Atomic Operations** are used to manage active tasks and stop conditions without additional locks.
- **Load Balancing** is dynamic, which makes task distribution more efficient but potentially uneven in some cases.

### **Potential Improvements for Both Methods**
- **Work-Stealing Mechanism**:
  - Implementing a **work-stealing strategy** could help balance workloads more effectively in the **adaptive method**, allowing idle threads to take over tasks from busier threads.
  
- **Lock-Free Data Structures**:
  - Utilizing **lock-free** or **concurrent data structures** could further reduce contention in task management, making the implementation more efficient for higher thread counts.

### **Conclusion**
The **non-adaptive trapezoidal integration** provides a simpler and more predictable way of ensuring balanced workloads due to **static task assignment**. In contrast, the **adaptive method** benefits from **dynamic workload distribution** to achieve higher accuracy but requires more sophisticated thread safety mechanisms to handle the variable nature of tasks. Both implementations use a combination of **mutexes**, **atomic variables**, and **condition variables** to guarantee **thread-safe execution**, ensuring that the results are correct and that threads do not interfere with one another.

This detailed explanation of thread safety provides insight into the strategies used to maintain robustness and correctness in both the **adaptive** and **non-adaptive trapezoidal integration** implementations.

---

This **README.md** section can be used to document the measures taken to ensure thread safety in your project for both the **adaptive** and **non-adaptive** methods. It highlights the specific strategies, including **mutexes**, **atomic variables**, **condition variables**, and **load balancing techniques**, that contribute to robust parallel implementation.
