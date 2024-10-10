# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Target executable
TARGET = brain_mesh.exe

# Source files
SRCS = main.cpp

# Header files
HDRS = brain_mesh.h brain_mesh_macros.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Python script
PYTHON_SCRIPT = plot_histograms.py

# Directories
IMG_DIR = images

# Default target
all: $(TARGET) histograms

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the Python script and generate histograms
histograms: $(TARGET) $(IMG_DIR)
	@echo "Running $(TARGET) to generate data files..."
	$(TARGET)
	@echo "Running Python script to generate histograms..."
	python $(PYTHON_SCRIPT)

# Rule to create the images directory if it doesn't exist
$(IMG_DIR):
	if not exist $(IMG_DIR) mkdir $(IMG_DIR)

# Clean up build files and generated data
clean:
	del /Q $(TARGET) $(OBJS) edge_lengths.txt vertex_areas.txt triangle_areas.txt
	if exist $(IMG_DIR) rmdir /S /Q $(IMG_DIR)

# Phony targets
.PHONY: all clean histograms
