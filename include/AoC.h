#pragma once

#include "Timer.h"
#include <cstdint>
#include <fstream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
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
        fin.close();
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

// Lazily splits `str` on `delimiter`, yielding std::string_views into `str` —
// no allocation, and parts are only produced as you iterate. The views borrow
// from `str`, so the source string must outlive the range. When you need
// random access or size(), materialize:
//   split(s, "\n") | std::ranges::to<std::vector<std::string>>()
inline auto split(std::string_view str, std::string_view delimiter)
{
    return str | std::views::split(delimiter) |
           std::views::transform([](auto&& part) { return std::string_view(part); });
}

} // namespace aoc
