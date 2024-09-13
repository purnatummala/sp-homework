# Define the compiler and flags
CXX = cl
CXXFLAGS = /EHsc

# Define the target executable
TARGET = homework2_skeleton.exe

# Define the source files
SRCS = homework2_skeleton.cpp

# Define the Python script
PYTHON_SCRIPT = plot_trajectories.py

# Default target
all: $(TARGET) run

# Compile the C++ code
$(TARGET): $(SRCS)
    $(CXX) $(CXXFLAGS) $(SRCS) /Fe$(TARGET)

# Run the executable and the Python script
run: $(TARGET)
    $(TARGET)
    python $(PYTHON_SCRIPT)

# Clean up the build files
clean:
    del $(TARGET) *.obj

.PHONY: all run clean