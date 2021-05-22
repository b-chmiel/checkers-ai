#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

class ProgressBar
{
public:
    ProgressBar(int totalTicks, double step);
    void Tick();
    void Print();

private:
    int m_TotalTicks;
    double m_Step;
    int m_Ticks;
};
#endif
