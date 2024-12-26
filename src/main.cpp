#include <iostream>
#include <memory>
#include "aoc.h"
#include "lib.h"

int main() {
    auto solution = std::make_unique<Solution05>("../inputs/2023/05.txt"); 
    auto [resultA, timeA] = solution->runAndTimePartA();
    auto [resultB, timeB] = solution->runAndTimePartB();

    std::cout << "🎄 Part A: " << resultA << " :: " << timeA << " ms" << std::endl;
    std::cout << "🎄 Part B: " << resultB << " :: " << timeB << " ms" << std::endl;
}