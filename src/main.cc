#include "Experiment/experiment.h"
#include "Experiment/skillsVsTreeDepth.h"
#include "Experiment/skillsVsTreeDepth_impl.h"
#include "Experiment/strategyEfficiency.h"
#include "Experiment/strategyEfficiency_impl.h"
#include "Experiment/timeEfficiency.h"
#include "Experiment/timeEfficiency_impl.h"
#include "MoveInput/MinMax/alphaBeta.h"
#include "MoveInput/MinMax/minMax.h"
#include <cstdlib>

int main()
{
    auto params = experiment::Params {
        .RandomMoves = 10,
        .GameCount = 10,
        .Delta = 0.01,
        .MaxDepth = 4
    };

    if (std::getenv("TIME_EFFICIENCY_A"))
    {
        std::cout << "TIME_EFFICIENCY_A" << std::endl;
        auto ex = TimeEfficiency(params);
        ex.Perform<minmax::MinMax, minmax::MinMax>();
    }

    params.MaxDepth = 4;

    if (std::getenv("TIME_EFFICIENCY_B"))
    {
        std::cout << "TIME_EFFICIENCY_B" << std::endl;
        auto ex = TimeEfficiency(params);
        ex.Perform<alpha_beta::AlphaBeta, alpha_beta::AlphaBeta>();
    }

    if (std::getenv("SKILLS_VS_DEPTH"))
    {
        std::cout << "SKILLS_VS_DEPTH" << std::endl;
        auto ex = SkillsVsTreeDepth(params);
        ex.Perform<alpha_beta::AlphaBeta, alpha_beta::AlphaBeta>();
    }

    if (std::getenv("STRATEGY_EFFICIENCY"))
    {
        std::cout << "STRATEGY_EFFICIENCY" << std::endl;
        auto ex = StrategyEfficiency(params);
        ex.Perform<EvaluateOne>();
    }

    // if (std::getenv("STRAGEGIES"))
    // {
    //     auto ex = TimeEfficiency(params);
    // }

    return 0;
}
