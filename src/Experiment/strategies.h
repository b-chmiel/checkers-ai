#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "experiment.h"

class Strategies
{
private:
    experiment::Params m_Params;

public:
    Strategies(const experiment::Params& params)
        : m_Params(params) {};

    template <class StrategyA, class StrategyB>
    void Perform(int maxDepth) const;
};

#endif
