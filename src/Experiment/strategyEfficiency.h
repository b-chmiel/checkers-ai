#ifndef STRATEGY_EFFICIENCY_H
#define STRATEGY_EFFICIENCY_H

#include "experiment.h"

class StrategyEfficiency
{
private:
    experiment::Params m_Params;

public:
    StrategyEfficiency(const experiment::Params& params)
        : m_Params(params) {};

    template <class Strategy>
    void Perform(int maxDepth) const;
};

#endif
