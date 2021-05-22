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

template <class InputMethod>
void TimeEfficiency::Perform() const
{
    std::shared_ptr<EvaluationFunction> player1Eval = std::make_shared<EvaluateOne>();
    std::shared_ptr<EvaluationFunction> player2Eval = std::make_shared<EvaluateOne>();

    std::vector<game_stats::TotalGameStats> stats;
    stats.reserve(m_Params.MaxDepth - 2);

    for (auto depth = 2; depth <= m_Params.MaxDepth; depth++)
    {
        std::cout << "\nDepth: " << depth << std::endl;

        std::shared_ptr<MoveInput> player1Ai = std::make_shared<InputMethod>(depth, player1Eval);
        std::shared_ptr<MoveInput> player2Ai = std::make_shared<InputMethod>(depth, player2Eval);

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