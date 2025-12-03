# Makefile for Process Executor Logger

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = process_executor_logger

# Source files
SOURCES = process_executor_logger.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean

.PHONY: cmake_build cmake_rebuild
cmake_build:
	mkdir build && cd build && cmake .. && cmake --build .
cmake_clean:
	@if exist build rmdir /s /q build
cmake_rebuild: cmake_clean cmake_build
