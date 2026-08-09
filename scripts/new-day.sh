#!/usr/bin/env bash
# Scaffold a new AoC solution file: new-day.sh <year> <day>
set -euo pipefail

if [ $# -ne 2 ]; then
    echo "usage: $0 <year> <day>" >&2
    exit 1
fi

year=$1
day=$2
dd=$(printf "%02d" "$day")
file="$year/$dd.cpp"

if [ -e "$file" ]; then
    echo "$file already exists" >&2
    exit 1
fi

mkdir -p "$year"
cat > "$file" <<EOF
#include "registry.h"

namespace aoc {

class Solution$dd final : public SolutionBase
{
public:
    using SolutionBase::SolutionBase;

    uint64_t partA() const override
    {
        return 0;
    }

    uint64_t partB() const override
    {
        return 0;
    }
};

AOC_REGISTER($year, $day, Solution$dd);

} // namespace aoc
EOF

echo "Created $file"
echo "Put your puzzle input at inputs/$year/$dd.txt, then: just run $year $day"
