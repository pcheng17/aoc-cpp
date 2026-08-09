#pragma once

#include "aoc.h"
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>

struct SolutionInfo
{
    std::function<std::unique_ptr<SolutionBase>(const std::string&)> factory;
    std::optional<uint64_t> expectedA;
    std::optional<uint64_t> expectedB;
};

// Ordered by (year, day) so --all runs chronologically.
using SolutionMap = std::map<std::pair<int, int>, SolutionInfo>;

class Registry
{
public:
    static Registry& instance()
    {
        static Registry registry;
        return registry;
    }

    void add(int year, int day, SolutionInfo info)
    {
        mSolutions.emplace(std::make_pair(year, day), std::move(info));
    }

    const SolutionMap& solutions() const { return mSolutions; }

private:
    Registry() = default;

    SolutionMap mSolutions;
};

struct Registrar
{
    Registrar(int year, int day, SolutionInfo info)
    {
        Registry::instance().add(year, day, std::move(info));
    }
};

// Registers a solution class for a given year/day. Optionally pass the known
// answers for parts A and B; the runner will verify them on every run:
//   AOC_REGISTER(2023, 5, Solution05)
//   AOC_REGISTER(2023, 5, Solution05, 1181555926, 37806486)
#define AOC_REGISTER(year, day, Class, ...)                                  \
    static const Registrar registrar_##year##_##day(                         \
        year, day,                                                           \
        SolutionInfo{                                                        \
            [](const std::string& filename)                                  \
                -> std::unique_ptr<SolutionBase> {                           \
                return std::make_unique<Class>(filename);                    \
            },                                                               \
            ##__VA_ARGS__ })
