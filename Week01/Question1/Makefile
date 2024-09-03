# Compiler
CC = cl

# Compiler flags
CFLAGS_DEBUG = /W3 /EHsc /Zi /std:c++17 /Od /Wall
CFLAGS_RELEASE = /W3 /EHsc /Zi /std:c++17 /O2 /Wall

# Default to release flags
CFLAGS = $(CFLAGS_RELEASE)

# Source files
SRCS_C = main.c file1.c file2.c
SRCS_CPP = generate_csv.cpp heat_distribution.cpp homework.cpp

# Object files
OBJS_C = main.obj file1.obj file2.obj
OBJS_CPP = generate_csv.obj heat_distribution.obj homework.obj

# Executables
EXECUTABLES = generate_csv.exe heat_distribution.exe homework.exe

# Default target
all: $(EXECUTABLES)

# Compile C source files into object files
.c.obj:
    $(CC) $(CFLAGS) /c $<

# Targets for different build types
debug: CFLAGS = $(CFLAGS_DEBUG)
debug: clean all

release: CFLAGS = $(CFLAGS_RELEASE)
release: clean all

# Clean up generated files
clean:
    del /Q $(OBJS_C) $(OBJS_CPP) $(EXECUTABLES)

.PHONY: all clean debug release
