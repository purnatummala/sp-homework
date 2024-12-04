# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -O2 -Wall -pthread

# Source files
ADAPTIVE_SRC = adaptive_trapezoidal.cpp
NON_ADAPTIVE_SRC = non_adaptive_trapezoidal.cpp

# Output executables
ADAPTIVE_EXEC = adaptive_trapezoidal
NON_ADAPTIVE_EXEC = non_adaptive_trapezoidal

# Python script for plotting
PLOT_SCRIPT = performance_analysis.py

# Default target
all: $(ADAPTIVE_EXEC) $(NON_ADAPTIVE_EXEC)

# Adaptive trapezoidal integration target
$(ADAPTIVE_EXEC): $(ADAPTIVE_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Non-adaptive trapezoidal integration target
$(NON_ADAPTIVE_EXEC): $(NON_ADAPTIVE_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run the compiled executables and generate CSV results
run: $(ADAPTIVE_EXEC) $(NON_ADAPTIVE_EXEC)
	./$(ADAPTIVE_EXEC)
	./$(NON_ADAPTIVE_EXEC)

# Generate plots using the Python script
plots: run
	python $(PLOT_SCRIPT)

# Clean up object files, executables, and generated CSV files
clean:
	rm -f $(ADAPTIVE_EXEC) $(NON_ADAPTIVE_EXEC) adaptive_trapezoidal_results.csv parallel_trapezoidal_results.csv

# PHONY targets
.PHONY: all clean run plots
