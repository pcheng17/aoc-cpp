#include "Registry.h"

namespace aoc {

class Solution02 final : public SolutionBase
{
public:
    using SolutionBase::SolutionBase;

    int64_t partA() const override
    {
        std::array<int, 26> counts{};
        int twos = 0;
        int threes = 0;
        for (const auto line : split(mInput, "\n"))
        {
            counts.fill(0);
            bool hasTwo = false;
            bool hasThree = false;
            for (const char c : line)
            {
                ++counts[c - 'a'];
            }
            for (const int count : counts)
            {
                if (count == 2 && !hasTwo)
                {
                    ++twos;
                    hasTwo = true;
                }
                else if (count == 3 && !hasThree)
                {
                    ++threes;
                    hasThree = true;
                }

                if (hasTwo && hasThree)
                {
                    break;
                }
            }
        }
        return twos * threes;
    }

    int64_t partB() const override
    {
        return 0;
    }
};

AOC_REGISTER(2018, 2, Solution02, 5704);

} // namespace aoc
