#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace timer
{
using time_point = std::chrono::steady_clock::time_point;

class Timer
{
public:
    time_point BeginTime;
    time_point EndTime;

    Timer() = default;
    double TimeDifferenceInSeconds() const;
    void Begin();
    void End();
};

}
#endif
