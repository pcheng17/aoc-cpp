# List available recipes
default:
    @just --list

# Configure the Release build (run once, or after editing CMakeLists.txt)
configure:
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Configure a Debug build in build-debug/
configure-debug:
    cmake -B build-debug -S . -DCMAKE_BUILD_TYPE=Debug

# Build (configures first if needed)
build:
    @test -d build || just configure
    cmake --build build

# Build the Debug variant
build-debug:
    @test -d build-debug || just configure-debug
    cmake --build build-debug

# Run all registered days
run-all: build
    ./build/aoc --all

# Run one day, e.g. `just run 2023 5`
run year day: build
    ./build/aoc {{year}} {{day}}

# Run one day against a custom input file, e.g. `just run-input 2023 5 sample.txt`
run-input year day input: build
    ./build/aoc {{year}} {{day}} --input {{input}}

# Delete all build directories
clean:
    rm -rf build build-debug
