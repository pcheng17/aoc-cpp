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
        std::vector<std::string_view> lines = split(mInput, "\n") | std::ranges::to<std::vector>();
        std::ranges::sort(lines);

        for (size_t i = 0; i < lines.size() - 1; ++i)
        {
            const std::string_view a = lines[i];
            const std::string_view b = lines[i + 1];
            int diffCount = 0;

            for (size_t j = 0; j < a.size(); ++j)
            {
                if (a[j] != b[j])
                {
                    ++diffCount;
                    if (diffCount > 1)
                    {
                        break;
                    }
                }
            }

            if (diffCount == 1)
            {
                std::string result;
                result.reserve(a.size() - 1);
                for (size_t j = 0; j < a.size(); ++j)
                {
                    if (a[j] == b[j])
                    {
                        result += a[j];
                    }
                }
                return result;
            }
        }

        return "No solution found";
    }
};

AOC_REGISTER(2018, 2, Solution02, 5704, "umdryabviapkozistwcnihjqx");

} // namespace aoc
