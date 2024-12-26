#include "Timer.h"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

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

    virtual uint64_t partA() const = 0;
    virtual uint64_t partB() const = 0;
protected:
    std::string mInput;
};

class Solution05 : public SolutionBase
{
public:
    using SolutionBase::SolutionBase;

    uint64_t partA() const override {
        return 0;
    }

    uint64_t partB() const override {
        return 0;
    }
};


using Integer = uint64_t;
using SeedRanges = std::vector<std::pair<Integer, Integer>>;
using MapRule = std::array<Integer, 3>;
using Map = std::vector<MapRule>;
using MapCollection = std::vector<Map>;

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.rfind(prefix, 0) == 0;
}

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

SeedRanges parseSeeds(const std::string& str) {
    SeedRanges seeds;
    const auto splits = split(str, " ");
    for (size_t i = 0; i < splits.size(); i += 2) {
        seeds.emplace_back(std::stoull(splits[i]), std::stoull(splits[i + 1]));
    }
    return seeds;
}

Map parseMap(const std::string& str) {
    Map map;
    const auto splits = split(str, "\n");
    for (size_t i = 1; i < splits.size(); ++i) {
        const auto lineSplits = split(splits[i], " ");
        map.push_back(
            std::array<Integer, 3>{
                static_cast<Integer>(std::stoull(lineSplits[0])), 
                static_cast<Integer>(std::stoull(lineSplits[1])), 
                static_cast<Integer>(std::stoull(lineSplits[2]))
            });
    }
    return map;
}

Integer binarySearch(const Map& map, Integer val) {
    if (val < map[0][0] || val > (map.back()[0] + map.back()[2])) {
        return val;
    }

    size_t left = 0;
    size_t right = map.size() - 1;
    while (left <= right) {
        const size_t mid = (left + right) / 2;
        const auto& [dst, src, rng] = map[mid];
        if (dst <= val && val < dst + rng) {
            return src + (val - dst);
        } else if (val < dst) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return val;
}

Integer inverseMap(const MapCollection& maps, const SeedRanges& seeds) {
    Integer current = 0;
    Integer t = 0;
    while (true) {
        for (int i = maps.size() - 1; i >= 0; --i) {
            // t = binarySearch(maps[i], t);

            for (const auto& [dst, src, rng] : maps[i]) {
                if (dst <= t && t < dst + rng) {
                    t = src + (t - dst);
                    break;
                }
            }
        }

        for (const auto &[start, rng] : seeds) {
            if (start <= t && t < start + rng) {
                return current;
            }
        }

        t = ++current;
    }
}


int main() {
    Timer timer;
    std::ifstream fin("./inputs/2023/05.txt");
    
    if (!fin.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << fin.rdbuf();

    fin.close();

    timer.start();
    const std::string content = buffer.str();
    const std::vector<std::string> groups = split(content, "\n\n");
    const SeedRanges seeds = parseSeeds(groups[0].substr(7));
    MapCollection maps;
    for (size_t i = 1; i < groups.size(); ++i) {
        maps.emplace_back(parseMap(groups[i]));
    }

    timer.stop();
    const auto parseTime = timer.getElapsedMilliseconds();

    timer.start();
    const auto answer = inverseMap(maps, seeds);
    timer.stop();
    const auto evalTime = timer.getElapsedMilliseconds();

    std::cout << "Parsing time: " << parseTime << " ms" << std::endl;
    std::cout << "Evaluation time: " << evalTime << " ms" << std::endl;
    std::cout << "Answer: " << answer << std::endl;
}