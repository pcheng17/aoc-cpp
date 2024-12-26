#pragma once

#include <chrono>

class Timer
{
public:
    void start() {
        mStart = std::chrono::high_resolution_clock::now();
        mRunning = true;
    }

    void stop() {
        if (mRunning) {
            mEnd = std::chrono::high_resolution_clock::now();
            mRunning = false;
        }
    }

    double getElapsedSeconds() const { return getElapsedTime<std::chrono::seconds>(); }
    double getElapsedMilliseconds() const { return getElapsedTime<std::chrono::milliseconds>(); }
    double getElapsedMicroseconds() const { return getElapsedTime<std::chrono::microseconds>(); }
    double getElapsedNanoseconds() const { return getElapsedTime<std::chrono::nanoseconds>(); }

private:
    template <typename Units>
    double getElapsedTime() const {
        if (mRunning) {
            return -1.0;
        }

        auto elapsed = std::chrono::duration_cast<Units>(mEnd - mStart);
        return elapsed.count();
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> mStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> mEnd;
    bool mRunning = false;
};