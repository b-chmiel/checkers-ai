#ifndef EXPERIMENT_H
#define EXPERIMENT_H

namespace experiment
{
struct Params
{
    int RandomMoves;
    int GameCount;
    double Delta;
};

class Experiment
{
public:
    virtual void Perform(int maxDepth) const = 0;
};
}

#endif