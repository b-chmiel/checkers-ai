#ifndef EXPERIMENT_H
#define EXPERIMENT_H

namespace experiment
{
struct Params
{
    bool IsMoveTiming;
    bool IsGameTiming;
    bool IsProgressiveDepth;
    int RandomMoves;
    int GameCount;
    double Delta;
    bool AlphaBeta;
    int MaxDepth;
};

class Experiment
{
public:
    virtual void Perform() const = 0;
};
}

#endif