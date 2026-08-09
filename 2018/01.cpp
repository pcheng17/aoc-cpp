#include "Registry.h"
#include <algorithm>
#include <charconv>
#include <unordered_set>

namespace aoc
{

class Solution01 final : public SolutionBase
{
public:
    using SolutionBase::SolutionBase;

    Answer partA() const override
    {
        int64_t result = 0;

        for (const auto line : split(mInput, "\n"))
        {
            if (line.empty())
                continue;
            result += parseNumber(line);
        }

        return result;
    }

    Answer partB() const override
    {
        int64_t result = 0;
        std::vector<int64_t> numbers;
        numbers.reserve(std::ranges::count(mInput, '\n') + 1);

        for (const auto line : split(mInput, "\n"))
        {
            if (line.empty())
                continue;
            numbers.push_back(parseNumber(line));
        }

        std::unordered_set<int64_t> seen;

        while (true)
        {
            for (const int64_t number : numbers)
            {
                result += number;
                if (seen.contains(result))
                {
                    return result;
                }
                seen.insert(result);
            }
        }

        return result;
    }

private:
    static int64_t parseNumber(std::string_view line)
    {
        int64_t value = 0;
        std::from_chars(line.data() + 1, line.data() + line.size(), value);
        return line[0] == '-' ? -value : value;
    }
};

AOC_REGISTER(2018, 1, Solution01, 569, 77666);

} // namespace aoc
