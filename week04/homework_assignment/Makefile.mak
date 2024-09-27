# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall

# Targets
TARGETS = main main_no_delete

# Source files
SOURCES_MAIN = main.cpp
SOURCES_MAIN_NO_DELETE = main1.cpp

# Object files
OBJECTS_MAIN = $(SOURCES_MAIN:.cpp=.o)
OBJECTS_MAIN_NO_DELETE = $(SOURCES_MAIN_NO_DELETE:.cpp=.o)

# Default target
all: $(TARGETS)

# Compile main
main: $(OBJECTS_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main_no_delete
main_no_delete: $(OBJECTS_MAIN_NO_DELETE)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean target
clean:
	del $(TARGETS).exe $(OBJECTS_MAIN) $(OBJECTS_MAIN_NO_DELETE)

# Run all executables
run: all
	@echo "Running main.exe"
	@./main.exe
	@echo "Running main_no_delete.exe"
	@./main_no_delete.exe

# Pattern rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean run