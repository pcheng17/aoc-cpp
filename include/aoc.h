#pragma once

#include "Timer.h"
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

class SolutionBase
{
public:
    SolutionBase(const std::string& filename)
    {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            throw std::runtime_error("Unable to open file");
        }

        std::stringstream buffer;
        buffer << fin.rdbuf();
        mInput = buffer.str();
        fin.close();
    }

    virtual ~SolutionBase() = default;

    virtual uint64_t partA() const = 0;
    virtual uint64_t partB() const = 0;

    std::pair<uint64_t, double> runAndTimePartA() const 
    {
        Timer timer;
        timer.start();
        uint64_t result = partA();
        timer.stop();
        return { result, timer.getElapsedMilliseconds() };
    }

    std::pair<uint64_t, double> runAndTimePartB() const 
    {
        Timer timer;
        timer.start();
        uint64_t result = partB();
        timer.stop();
        return { result, timer.getElapsedMilliseconds() };
    }

protected:
    std::string mInput;
};

std::vector<std::string> 
split(const std::string& str, const std::string& delimiter) 
{
    std::vector<std::string> splits;
    size_t last = 0;
    size_t next = 0;
    while ((next = str.find(delimiter, last)) != std::string::npos) {
        splits.push_back(str.substr(last, next - last));
        last = next + delimiter.size();
    }
    splits.push_back(str.substr(last));
    return splits;
}