#pragma once

#include "Timer.h"
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc
{

struct TimedResult
{
    int64_t answer;
    double milliseconds;
};

class SolutionBase
{
public:
    explicit SolutionBase(const std::string& filename)
    {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        std::stringstream buffer;
        buffer << fin.rdbuf();
        mInput = buffer.str();
    }

    virtual ~SolutionBase() = default;

    virtual int64_t partA() const = 0;
    virtual int64_t partB() const = 0;

    TimedResult runAndTimePartA() const
    {
        return runAndTime([this] { return partA(); });
    }

    TimedResult runAndTimePartB() const
    {
        return runAndTime([this] { return partB(); });
    }

protected:
    std::string mInput;

private:
    template<typename Fn>
    TimedResult runAndTime(Fn&& fn) const
    {
        Timer timer;
        timer.start();
        int64_t answer = fn();
        timer.stop();
        return {answer, timer.getElapsedMilliseconds()};
    }
};

inline std::vector<std::string> split(const std::string& str, const std::string& delimiter)
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

} // namespace aoc
