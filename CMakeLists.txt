# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(AdventOfCode)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-O3")

# Include directories
include_directories(include)
include_directories(.)

# Add the executable
add_executable(aoc src/main.cpp)

# Specify additional files to be included in the compilation
# Assuming your 2023 directory contains multiple cpp files,
# list them all here separated by spaces.
# Example: 2023/05.cpp 2023/anotherFile.cpp
# target_sources(AdventOfCode PRIVATE 2023/05.cpp)
