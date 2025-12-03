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

cmake_build:
	@cmake -E make_directory build
	@cd build && cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded
	@cmake --build build --config Release

cmake_clean:
	@cmake -E remove_directory build

cmake_rebuild: cmake_clean cmake_build

# Phony targets
.PHONY: all clean cmake_build cmake_clean cmake_rebuild