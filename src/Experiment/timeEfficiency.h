#ifndef TIME_EFFICIENCY_H
#define TIME_EFFICIENCY_H

#include "experiment.h"

class TimeEfficiency : public experiment::Experiment
{
public:
    TimeEfficiency(const experiment::Params&);
    void Perform() const override;

private:
    experiment::Params m_Params;
    void NoAlphaBeta() const;
};

#endif