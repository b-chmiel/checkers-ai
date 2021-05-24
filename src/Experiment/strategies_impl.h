#ifndef STRATEGIES_IMPL
#define STRATEGIES_IMPL

#include "../Board/board.h"
#include "../MoveInput/MinMax/EvaluationFunction/evaluateOne.h"
#include "../MoveInput/MinMax/EvaluationFunction/evaluationFunction.h"
#include "../MoveInput/MinMax/alphaBeta.h"
#include "../MoveInput/MinMax/minMax.h"
#include "../MoveInput/moveInput.h"
#include "Utils/game.h"
#include "Utils/gameStats.h"
#include "Utils/progressBar.h"
#include "experiment.h"
#include "strategies.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

template <class StrategyA, class StrategyB>
void Strategies::Perform(int maxDepth) const
{
    auto strategyA = std::make_shared<StrategyA>(m_Params.Delta);
    auto player1Ai = std::make_shared<alpha_beta::AlphaBeta>(maxDepth, strategyA);

    auto strategyB = std::make_shared<StrategyB>(m_Params.Delta);
    auto player2Ai = std::make_shared<alpha_beta::AlphaBeta>(maxDepth, strategyB);
    std::vector<game_stats::TotalGameStats> stats;

    auto gameParams = game::GameParams {
        .player1Ai = player1Ai,
        .player2Ai = player2Ai,
        .params = m_Params
    };

    auto game = game::Game(gameParams);
    auto totalStats = game_stats::TotalGameStats(0);
    ProgressBar progress(m_Params.GameCount, 1);

    progress.Print();
    for (auto i = 0; i < m_Params.GameCount; i++)
    {
        totalStats.AppendGame(game.PlayGame());
        progress.Tick();
    }

    stats.push_back(totalStats);

    game_stats::TotalGameStats::ShowMany(stats);
}

#endif