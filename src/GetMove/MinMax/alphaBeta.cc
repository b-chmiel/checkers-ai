#include "alphaBeta.h"
#include "../../DrawBoard/board.h"
#include "../../Utils/move.h"
#include "../availableMoves.h"
#include "EvaluationFunction/evaluateOne.h"
#include "ratedMove.h"
#include <algorithm>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

using namespace alpha_beta;

int counter = 0;

AlphaBeta::AlphaBeta(int depth)
    : m_Depth(depth)
{
}

std::optional<Move> AlphaBeta::GetMove(board::Checkerboard& state)
{
    counter = 0;
    auto result = MinMaxDecision(state, m_Depth);

    std::cout << "Nodes: " << counter << std::endl;

    if (result.size() == 0)
    {
        return std::nullopt;
    }

    return (*result.rbegin()).Move;
}

rated_move::rated_move_set AlphaBeta::MinMaxDecision(board::Checkerboard& state, int depth)
{
    double value;
    rated_move::rated_move_set ratedMoves(rated_move::MoveComparison {});
    auto availableMoves = AvailableMoves::GetAvailableMoves(state, state.CurrentPlayer.Type);

    for (const auto& move : availableMoves)
    {
        auto isMaximizingPlayer = true;
        auto params = Params { -10, 10 };
        auto copyState = state;
        copyState.MovePiece(move);
        value = MinimaxValue(copyState, isMaximizingPlayer, depth, params);

        ratedMoves.insert({ value, move });
    }

    return ratedMoves;
}

double AlphaBeta::MinimaxValue(board::Checkerboard& state, bool isMaximizingPlayer, int depth, Params& params)
{
    auto availableMoves = AvailableMoves::GetAvailableMoves(state, state.CurrentPlayer.Type);

    if (TerminalTest(state, availableMoves, depth))
    {
        counter++;
        EvaluateOne e;
        return e.Evaluate(state);
    }
    else if (isMaximizingPlayer)
    {
        return MaxValue(state, availableMoves, depth, params);
    }
    else
    {
        return MinValue(state, availableMoves, depth, params);
    }
}

bool AlphaBeta::TerminalTest(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth)
{
    return state.IsGameCompleted() || availableMoves.size() == 0 || depth == 0;
}

double AlphaBeta::MaxValue(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth, Params& params)
{
    for (const auto& move : availableMoves)
    {
        auto copyState = state;
        copyState.MovePiece(move);
        params.Alpha = std::max(params.Alpha, MinimaxValue(copyState, false, depth - 1, params));
        if (params.Alpha >= params.Beta)
        {
            break;
        }
    }

    return params.Alpha;
}

double AlphaBeta::MinValue(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth, Params& params)
{
    for (const auto& move : availableMoves)
    {
        auto copyState = state;
        copyState.MovePiece(move);
        params.Beta = std::min(params.Beta, MinimaxValue(copyState, true, depth - 1, params));
        if (params.Alpha >= params.Beta)
        {
            break;
        }
    }

    return params.Beta;
}
