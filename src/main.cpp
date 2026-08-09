#include "Registry.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace
{

std::string defaultInputPath(aoc::PuzzleId id)
{
    std::ostringstream path;
    path << "inputs/" << id.year << "/" << std::setw(2) << std::setfill('0') << id.day << ".txt";
    return path.str();
}

std::string resolveInputPath(aoc::PuzzleId id)
{
    const std::string relative = defaultInputPath(id);
    if (std::ifstream(relative).good()) {
        return relative;
    }
    // Fall back to running from a build subdirectory (e.g. build/).
    return "../" + relative;
}

bool checkAnswer(const char* label, const aoc::Answer& actual, const std::optional<aoc::Answer>& expected)
{
    if (expected && actual != *expected) {
        std::cout << "   ❌ Part " << label << ": got " << actual << ", expected " << *expected
                  << std::endl;
        return false;
    }
    return true;
}

bool runSolution(aoc::PuzzleId id, const aoc::SolutionInfo& info, const std::string& inputOverride)
{
    const std::string inputPath = inputOverride.empty() ? resolveInputPath(id) : inputOverride;

    std::cout << "🎄 " << id.year << " Day " << std::setw(2) << std::setfill('0') << id.day
              << std::endl;

    try {
        const auto solution = info.factory(inputPath);
        const aoc::TimedResult a = solution->runAndTimePartA();
        const aoc::TimedResult b = solution->runAndTimePartB();

        std::cout << std::fixed << std::setprecision(3)
                  << "   Part A: " << a.answer << " :: " << a.milliseconds << " ms\n"
                  << "   Part B: " << b.answer << " :: " << b.milliseconds << " ms" << std::endl;

        const bool okA = checkAnswer("A", a.answer, info.expectedA);
        const bool okB = checkAnswer("B", b.answer, info.expectedB);
        return okA && okB;
    } catch (const std::exception& error) {
        std::cout << "   ⚠️  " << error.what() << std::endl;
        return false;
    }
}

bool runAll()
{
    bool allOk = true;
    for (const auto& [id, info] : aoc::Registry::instance().solutions()) {
        allOk = runSolution(id, info, "") && allOk;
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

    const aoc::PuzzleId id{std::stoi(argv[1]), std::stoi(argv[2])};
    const std::string inputOverride = argc == 5 ? argv[4] : "";

    const auto& solutions = aoc::Registry::instance().solutions();
    const auto it = solutions.find(id);
    if (it == solutions.end()) {
        std::cout << "No solution registered for " << id.year << " day " << id.day << std::endl;
        return 1;
    }

    return runSolution(id, it->second, inputOverride) ? 0 : 1;
}
