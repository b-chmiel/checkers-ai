#ifndef ONE_GAME_H
#define ONE_GAME_H

#include "experiment.h"

class OneGame
{
private:
    experiment::Params m_Params;

public:
    OneGame(const experiment::Params& params)
        : m_Params(params) {};

    template <class InputMethodA, class InputMethodB>
    void Perform(int maxDepth) const;
};

#endif
