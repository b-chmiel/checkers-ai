#include "timer.h"
#include <chrono>

using namespace timer;

double Timer::TimeDifferenceInSeconds() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(EndTime - BeginTime).count() / 1000000.0;
}

void Timer::Begin()
{
    BeginTime = std::chrono::steady_clock::now();
}

void Timer::End()
{
    EndTime = std::chrono::steady_clock::now();
}