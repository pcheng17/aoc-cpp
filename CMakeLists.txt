cmake_minimum_required(VERSION 3.12)

project(AdventOfCode CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Every year directory contributes one .cpp per solved day; each file
# self-registers with the runner via AOC_REGISTER.
file(GLOB SOLUTION_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/20*/*.cpp")

add_executable(aoc src/main.cpp ${SOLUTION_SOURCES})
target_include_directories(aoc PRIVATE include)
