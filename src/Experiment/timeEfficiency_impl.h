#ifndef TIME_EFFICIENCY_TCC
#define TIME_EFFICIENCY_TCC

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
#include "timeEfficiency.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

template <class InputMethodA, class InputMethodB>
void TimeEfficiency::Perform(int maxDepth) const
{
    auto player1Eval = std::make_shared<EvaluateOne>(m_Params.Delta);
    auto player2Eval = std::make_shared<EvaluateOne>(m_Params.Delta);

    std::vector<game_stats::TotalGameStats> stats;

    for (auto depth = 1; depth <= maxDepth; depth++)
    {
        std::cout << "\nDepth: " << depth << std::endl;

        auto player1Ai = std::make_shared<InputMethodA>(depth, player1Eval);
        auto player2Ai = std::make_shared<InputMethodB>(depth, player2Eval);

        auto gameParams = game::GameParams {
            .player1Ai = player1Ai,
            .player2Ai = player2Ai,
            .params = m_Params
        };

        auto game = game::Game(gameParams);
        auto totalStats = game_stats::TotalGameStats(depth);
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