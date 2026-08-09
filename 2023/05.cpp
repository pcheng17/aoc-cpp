#include "registry.h"
#include <array>
#include <vector>

class Solution05 final : public SolutionBase
{
public:
    using SolutionBase::SolutionBase;

    using SeedRanges = std::vector<std::pair<uint64_t, uint64_t>>;
    using MapRule = std::array<uint64_t, 3>;
    using Map = std::vector<MapRule>;
    using MapCollection = std::vector<Map>;

    uint64_t partA() const override
    {
        return 0;
    }

    uint64_t partB() const override
    {
        const std::vector<std::string> groups = split(mInput, "\n\n");
        const SeedRanges seeds = parseSeeds(groups[0].substr(7));
        MapCollection maps;
        for (size_t i = 1; i < groups.size(); ++i) {
            maps.emplace_back(parseMap(groups[i]));
        }
        uint64_t current = 0;
        uint64_t t = 0;
        while (true) {
            for (int i = maps.size() - 1; i >= 0; --i) {
                for (const auto& [dst, src, rng] : maps[i]) {
                    if (dst <= t && t < dst + rng) {
                        t = src + (t - dst);
                        break;
                    }
                }
            }

            for (const auto& [start, rng] : seeds) {
                if (start <= t && t < start + rng) {
                    return current;
                }
            }

            t = ++current;
        }
    }

private:
    SeedRanges parseSeeds(const std::string& str) const
    {
        SeedRanges seeds;
        const auto splits = split(str, " ");
        for (size_t i = 0; i < splits.size(); i += 2) {
            seeds.emplace_back(std::stoull(splits[i]), std::stoull(splits[i + 1]));
        }
        return seeds;
    }

    Map parseMap(const std::string& str) const
    {
        Map map;
        const auto splits = split(str, "\n");
        for (size_t i = 1; i < splits.size(); ++i) {
            if (splits[i].empty()) {
                continue;
            }
            const auto lineSplits = split(splits[i], " ");
            map.push_back(MapRule{
                std::stoull(lineSplits[0]),
                std::stoull(lineSplits[1]),
                std::stoull(lineSplits[2]) });
        }
        return map;
    }
};

// AOC_REGISTER(2023, 5, Solution05);
