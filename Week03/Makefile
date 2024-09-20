# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Targets
TARGET = main
TEST_TARGET = test_grid

# Source files
SRCS = main.cpp Grid1.cpp Grid2.cpp Grid3.cpp
TEST_SRCS = test_grid.cpp Grid1.cpp Grid2.cpp Grid3.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Build main target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build test target
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)

# Run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run main program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean test run
