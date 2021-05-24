#ifndef TIME_EFFICIENCY_H
#define TIME_EFFICIENCY_H

#include "experiment.h"

class TimeEfficiency
{
private:
    experiment::Params m_Params;

public:
    TimeEfficiency(const experiment::Params& params)
        : m_Params(params) {};

    template <class InputMethodA, class InputMethodB>
    void Perform(int maxDepth) const;
};

#endif