#include "Registry.h"
#include <iostream>

namespace aoc
{

class Solution01 final : public SolutionBase
{
public:
    using SolutionBase::SolutionBase;

    int64_t partA() const override
    {
        int64_t result = 0;
        std::vector<std::string> lines = split(mInput, "\n");

        for (const auto& line : lines)
        {
            if (line.empty())
                continue;
            result += (line[0] == '+' ? std::stoll(line.substr(1)) : -std::stoll(line.substr(1)));
        }

        return result;
    }

    int64_t partB() const override { return 0; }
};

AOC_REGISTER(2018, 1, Solution01);

} // namespace aoc
