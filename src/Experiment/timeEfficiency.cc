#include "timeEfficiency.h"
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
#include <memory>

TimeEfficiency::TimeEfficiency(const experiment::Params& params)
    : m_Params(params)
{
}

void TimeEfficiency::Perform() const
{
    NoAlphaBeta();
}

void TimeEfficiency::NoAlphaBeta() const
{
    const int depth = m_Params.MaxDepth;
    std::shared_ptr<EvaluationFunction> player1Eval = std::make_shared<EvaluateOne>();
    std::shared_ptr<EvaluationFunction> player2Eval = std::make_shared<EvaluateOne>();
    std::shared_ptr<MoveInput> player1Ai = std::make_shared<minmax::MinMax>(depth, player1Eval);
    std::shared_ptr<MoveInput> player2Ai = std::make_shared<minmax::MinMax>(depth, player2Eval);

    auto gameParams = game::GameParams {
        .player1Ai = player1Ai,
        .player2Ai = player2Ai,
        .params = m_Params
    };

    auto game = game::Game(gameParams);
    auto totalStats = game_stats::TotalGameStats(m_Params.MaxDepth);
    ProgressBar progress(m_Params.GameCount, 1);

    progress.Print();
    for (auto i = 0; i < m_Params.GameCount; i++)
    {
        totalStats.AppendGame(game.PlayGame());
        progress.Tick();
    }

    totalStats.Show();
}
