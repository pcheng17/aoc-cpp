#include "Registry.h"
#include <algorithm>
#include <vector>

namespace aoc
{

class Solution03 final : public SolutionBase
{
public:
    using SolutionBase::SolutionBase;

    struct Claim
    {
        uint32_t id, x, y, sx, sy;
    };

    Answer partA() const override
    {
        const auto [claims, fabric, height] = paint();
        return std::count_if(fabric.begin(), fabric.end(), [](uint8_t count) { return count > 1; });
    }

    Answer partB() const override
    {
        const auto [claims, fabric, height] = paint();

        for (const Claim& c : claims) {
            bool intact = true;
            for (uint32_t x = c.x; intact && x < c.x + c.sx; ++x) {
                for (uint32_t y = c.y; y < c.y + c.sy; ++y) {
                    if (fabric[static_cast<size_t>(x) * height + y] != 1) {
                        intact = false;
                        break;
                    }
                }
            }
            if (intact) {
                return c.id;
            }
        }

        return 0;
    }

private:
    struct Data
    {
        std::vector<Claim> claims;
        std::vector<uint8_t> fabric;
        uint32_t height;
    };

    Data paint() const
    {
        std::vector<Claim> claims;
        claims.reserve(std::ranges::count(mInput, '\n') + 1);
        uint32_t width = 0, height = 0;

        for (const auto line : split(mInput, "\n")) {
            Claim c;
            sscanf(line.data(), "#%u @ %u,%u: %ux%u", &c.id, &c.x, &c.y, &c.sx, &c.sy);
            width = std::max(width, c.x + c.sx);
            height = std::max(height, c.y + c.sy);
            claims.push_back(c);
        }

        std::vector<uint8_t> fabric(static_cast<size_t>(width) * height, 0);

        for (const Claim& c : claims) {
            for (uint32_t x = c.x; x < c.x + c.sx; ++x) {
                for (uint32_t y = c.y; y < c.y + c.sy; ++y) {
                    ++fabric[static_cast<size_t>(x) * height + y];
                }
            }
        }

        return {std::move(claims), std::move(fabric), height};
    }
};

AOC_REGISTER(2018, 3, Solution03, 116920, 382);

} // namespace aoc
