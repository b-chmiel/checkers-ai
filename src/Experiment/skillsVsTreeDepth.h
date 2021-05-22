#ifndef SKILLS_VS_TREE_DEPTH_H
#define SKILLS_VS_TREE_DEPTH_H

#include "experiment.h"

class SkillsVsTreeDepth
{
private:
    experiment::Params m_Params;

public:
    SkillsVsTreeDepth(const experiment::Params& params)
        : m_Params(params) {};

    template <class InputMethodA, class InputMethodB>
    void Perform() const;
};

#endif
