#ifndef STRATEGY_EFFICIENCY_IMPL
#define STRATEGY_EFFICIENCY_IMPL

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
#include "strategyEfficiency.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

template <class Strategy>
void StrategyEfficiency::Perform(int maxDepth) const
{
    const double minDelta = 0.0;
    const double maxDelta = 0.25;

    auto normalVersion = std::make_shared<Strategy>(0);
    auto player1Ai = std::make_shared<alpha_beta::AlphaBeta>(maxDepth, normalVersion);

    std::vector<game_stats::TotalGameStats> stats;

    for (auto delta = minDelta; delta < maxDelta; delta += 0.025)
    {
        std::cout << "\nDelta: " << delta << std::endl;

        auto randomizedVersion = std::make_shared<Strategy>(delta);
        auto player2Ai = std::make_shared<alpha_beta::AlphaBeta>(maxDepth, randomizedVersion);

        auto gameParams = game::GameParams {
            .player1Ai = player1Ai,
            .player2Ai = player2Ai,
            .params = m_Params
        };

        auto game = game::Game(gameParams);
        auto totalStats = game_stats::TotalGameStats(delta);
        ProgressBar progress(m_Params.GameCount, 1);

        progress.Print();
        for (auto i = 0; i < m_Params.GameCount; i++)
        {
            totalStats.AppendGame(game.PlayGame());
            progress.Tick();
        }

        stats.push_back(totalStats);
    }

    game_stats::TotalGameStats::ShowMany(stats);
}

#endif