#include "registry.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace {

std::string defaultInputPath(int year, int day)
{
    std::ostringstream path;
    path << "inputs/" << year << "/"
         << std::setw(2) << std::setfill('0') << day << ".txt";
    return path.str();
}

std::string resolveInputPath(int year, int day)
{
    const std::string relative = defaultInputPath(year, day);
    if (std::ifstream(relative).good()) {
        return relative;
    }
    // Fall back to running from a build subdirectory (e.g. build/).
    return "../" + relative;
}

bool checkAnswer(const char* label, uint64_t actual,
                 const std::optional<uint64_t>& expected)
{
    if (expected && actual != *expected) {
        std::cout << "   ❌ Part " << label << ": got " << actual
                  << ", expected " << *expected << std::endl;
        return false;
    }
    return true;
}

bool runSolution(int year, int day, const SolutionInfo& info,
                 const std::string& inputOverride)
{
    const std::string inputPath = inputOverride.empty()
        ? resolveInputPath(year, day)
        : inputOverride;

    std::cout << "🎄 " << year << " Day "
              << std::setw(2) << std::setfill('0') << day << std::endl;

    try {
        const auto solution = info.factory(inputPath);
        const auto [resultA, timeA] = solution->runAndTimePartA();
        const auto [resultB, timeB] = solution->runAndTimePartB();

        std::cout << "   Part A: " << resultA << " :: " << timeA << " ms\n"
                  << "   Part B: " << resultB << " :: " << timeB << " ms"
                  << std::endl;

        const bool okA = checkAnswer("A", resultA, info.expectedA);
        const bool okB = checkAnswer("B", resultB, info.expectedB);
        return okA && okB;
    } catch (const std::exception& error) {
        std::cout << "   ⚠️  " << error.what() << std::endl;
        return false;
    }
}

bool runAll()
{
    bool allOk = true;
    for (const auto& [key, info] : Registry::instance().solutions()) {
        allOk = runSolution(key.first, key.second, info, "") && allOk;
    }
    return allOk;
}

void printUsage(const char* program)
{
    std::cout << "Usage:\n"
              << "  " << program << "                       run all solutions\n"
              << "  " << program << " --all                 run all solutions\n"
              << "  " << program << " <year> <day>          run one solution\n"
              << "  " << program << " <year> <day> --input <path>" << std::endl;
}

} // namespace

int main(int argc, char** argv)
{
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "--all")) {
        return runAll() ? 0 : 1;
    }

    if (argc != 3 && !(argc == 5 && std::string(argv[3]) == "--input")) {
        printUsage(argv[0]);
        return 1;
    }

    const int year = std::stoi(argv[1]);
    const int day = std::stoi(argv[2]);
    const std::string inputOverride = argc == 5 ? argv[4] : "";

    const auto& solutions = Registry::instance().solutions();
    const auto it = solutions.find({ year, day });
    if (it == solutions.end()) {
        std::cout << "No solution registered for " << year << " day " << day
                  << std::endl;
        return 1;
    }

    return runSolution(year, day, it->second, inputOverride) ? 0 : 1;
}
