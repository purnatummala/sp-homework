# Benchmarks
Below is the list of variables to output when performing the benchmarks using the list of complicated functions in `complicated_functions.cpp`. Each benchmark will run all 
eight integration methods with no cache, with slow cache, and with fast cache. 
The tolerance will be set to 1.e-8 in all cases. The maximum depth for recursion will 
be set to 12. The maximum number of intervals used to compute the integrals will be 
set to 2048. 

#### method_name 
Name of the integration method. There are 8 methods
and the names should be descriptive and uniquely identify
each method

---

#### function_name 
Descriptive name of the function being integrated

---

#### cache_type 
Fast or slow cache

---

#### numerical_result 
Results of the integration 

---

#### absolute_error 
Absolute error estimate

---

### relative_error 
Relative error estimate

---

#### function_evaluations 
Number of function evaluations
The evaluation of a function already in cache 
does not count as an evaluation

---

#### execution_time_sec 
Time it takes to evaluate the integral in sec. Use
scientific notation (1.3e-5) rather than (0.000013)

---

#### cache_enabled 
Is function evaluation cache enabled (true/false)

