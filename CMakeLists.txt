cmake_minimum_required(VERSION 3.10)

project(ProcessExecutorLogger)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(process_executor_logger process_executor_logger.cpp)
