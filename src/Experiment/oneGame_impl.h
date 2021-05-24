#ifndef ONE_GAME_IMPL
#define ONE_GAME_IMPL

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
#include "oneGame.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

template <class InputMethodA, class InputMethodB>
void OneGame::Perform(int maxDepth) const
{
    auto player1Eval = std::make_shared<EvaluateOne>(m_Params.Delta);
    auto player2Eval = std::make_shared<EvaluateOne>(m_Params.Delta);

    std::vector<game_stats::TotalGameStats> stats;

    auto player1Ai = std::make_shared<InputMethodA>(maxDepth, player1Eval);
    auto player2Ai = std::make_shared<InputMethodB>(maxDepth, player2Eval);

    auto gameParams = game::GameParams {
        .player1Ai = player1Ai,
        .player2Ai = player2Ai,
        .params = m_Params
    };

    auto game = game::Game(gameParams);
    auto totalStats = game_stats::TotalGameStats(maxDepth);

    totalStats.AppendGame(game.PlayGame());

    stats.push_back(totalStats);

    game_stats::TotalGameStats::ShowMany(stats);
}

#endif