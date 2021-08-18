#include "Experiment/experiment.h"
#include "Experiment/oneGame.h"
#include "Experiment/oneGame_impl.h"
#include "Experiment/skillsVsTreeDepth.h"
#include "Experiment/skillsVsTreeDepth_impl.h"
#include "Experiment/strategies.h"
#include "Experiment/strategies_impl.h"
#include "Experiment/strategyEfficiency.h"
#include "Experiment/strategyEfficiency_impl.h"
#include "Experiment/timeEfficiency.h"
#include "Experiment/timeEfficiency_impl.h"
#include "MoveInput/MinMax/EvaluationFunction/evaluateOne.h"
#include "MoveInput/MinMax/EvaluationFunction/evaluateTwo.h"
#include "MoveInput/MinMax/alphaBeta.h"
#include "MoveInput/MinMax/minMax.h"
#include "MoveInput/User/userInput.h"
#include <cstdlib>
#include <string>
#include <vector>

int main()
{
    int gameCount = 10;
    double delta = 0.0;

    if (std::getenv("GAME_COUNT"))
    {
        gameCount = std::stoi(std::getenv("GAME_COUNT"));
    }

    if (std::getenv("DELTA"))
    {
        delta = std::stod(std::getenv("DELTA"));
    }

    auto params = experiment::Params {
        .RandomMoves = 10,
        .GameCount = gameCount,
        .Delta = delta,
    };

    if (std::getenv("TIME_EFFICIENCY_A"))
    {
        std::cout << "TIME_EFFICIENCY_A" << std::endl;
        auto ex = TimeEfficiency(params);
        const int depth = std::stoi(std::getenv("TIME_EFFICIENCY_A"));
        ex.Perform<minmax::MinMax, minmax::MinMax>(depth);
    }

    if (std::getenv("TIME_EFFICIENCY_B"))
    {
        std::cout << "TIME_EFFICIENCY_B" << std::endl;
        auto ex = TimeEfficiency(params);
        const int depth = std::stoi(std::getenv("TIME_EFFICIENCY_B"));
        ex.Perform<alpha_beta::AlphaBeta, alpha_beta::AlphaBeta>(depth);
    }

    // if (std::getenv("SKILLS_VS_DEPTH"))
    {
        std::cout << "SKILLS_VS_DEPTH" << std::endl;
        auto ex = SkillsVsTreeDepth(params);
        const int depth = 5; //std::stoi(std::getenv("SKILLS_VS_DEPTH"));
        ex.Perform<minmax::MinMax, minmax::MinMax>(depth);
    }

    if (std::getenv("STRATEGY_EFFICIENCY"))
    {
        std::cout << "STRATEGY_EFFICIENCY" << std::endl;
        auto ex = StrategyEfficiency(params);
        const int depth = std::stoi(std::getenv("STRATEGY_EFFICIENCY"));
        ex.Perform<EvaluateOne>(depth);
    }

    if (std::getenv("STRATEGIES"))
    {
        std::cout << "STRATEGIES" << std::endl;
        auto ex = Strategies(params);
        const int depth = std::stoi(std::getenv("STRATEGIES"));
        ex.Perform<EvaluateOne, EvaluateTwo>(depth);
    }

    if (std::getenv("USER_INPUT"))
    {
        std::cout << "USER_INPUT" << std::endl;
        auto ex = SkillsVsTreeDepth(params);
        const int depth = std::stoi(std::getenv("USER_INPUT"));
        ex.Perform<alpha_beta::AlphaBeta, UserInput>(depth);
    }

    // auto ex = OneGame(params);
    // ex.Perform<alpha_beta::AlphaBeta, alpha_beta::AlphaBeta>(1);

    return 0;
}
