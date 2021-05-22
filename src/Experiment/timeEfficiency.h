#ifndef TIME_EFFICIENCY_H
#define TIME_EFFICIENCY_H

#include "experiment.h"

class TimeEfficiency
{
public:
    TimeEfficiency(const experiment::Params&);

    template <class InputMethod>
    void Perform() const;

private:
    experiment::Params m_Params;
};

#endif