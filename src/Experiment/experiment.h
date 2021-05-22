#ifndef EXPERIMENT_H
#define EXPERIMENT_H

namespace experiment
{
struct Params
{
};

class Experiment
{
public:
    void Play(const Params&) const;
};
}

#endif