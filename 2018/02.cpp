#include "Registry.h"
#include <algorithm>

namespace aoc {

class Solution02 final : public SolutionBase
{
public:
    using SolutionBase::SolutionBase;

    Answer partA() const override
    {
        std::array<int, 26> counts{};
        int twos = 0;
        int threes = 0;
        for (const auto line : split(mInput, "\n"))
        {
            counts.fill(0);
            for (const char c : line)
            {
                ++counts[c - 'a'];
            }
            twos += int(std::ranges::contains(counts, 2));
            threes += int(std::ranges::contains(counts, 3));
        }
        return twos * threes;
    }

    Answer partB() const override
    {
        return 0;
    }
};

AOC_REGISTER(2018, 2, Solution02, 5704);

} // namespace aoc
