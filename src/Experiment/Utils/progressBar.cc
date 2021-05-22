#include "progressBar.h"
#include <iostream>

ProgressBar::ProgressBar(int totalTicks, double step)
    : m_TotalTicks(totalTicks)
    , m_Step(step)
    , m_Ticks(0)
{
}

void ProgressBar::Tick()
{
    m_Ticks += m_Step;
    Print();
}

//https://stackoverflow.com/a/14539953/11938328
void ProgressBar::Print()
{
    float progress = (float)m_Ticks / m_TotalTicks;
    const int width = 70;

    std::cout << '[';
    int pos = width * progress;
    for (int i = 0; i < width; ++i)
    {
        if (i < pos)
            std::cout << '=';
        else if (i == pos)
            std::cout << '>';
        else
            std::cout << ' ';
    }
    std::cout << "] " << int(progress * 100.0) << " % [" << m_Ticks << "/" << m_TotalTicks << "]\r";
    std::cout.flush();
}