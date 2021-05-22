#include "alphaBeta.h"
#include "../../Board/board.h"
#include "../../Utils/move.h"
#include "../availableMoves.h"
#include "EvaluationFunction/evaluationFunction.h"
#include "ratedMove.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

using namespace alpha_beta;

AlphaBeta::AlphaBeta(int depth, std::shared_ptr<EvaluationFunction> eval)
    : m_Depth(depth)
    , m_Nodes(0)
    , m_EvalFunction(eval)
{
}

std::optional<Move> AlphaBeta::ProcessMove(const board::Checkerboard& state, int moveCount)
{
    m_Nodes = 0;
    m_Player = state.CurrentPlayer;
    m_MoveCount = moveCount;

    auto result = MinMaxDecision(state, m_Depth - 1);

    // std::cout << "Nodes: " << m_Nodes << std::endl;

    if (result.size() == 0)
    {
        return std::nullopt;
    }

    return (*result.rbegin()).Move;
}

rated_move::rated_move_set AlphaBeta::MinMaxDecision(const board::Checkerboard& state, int depth)
{
    double value;
    rated_move::rated_move_set ratedMoves(rated_move::MoveComparison {});
    auto availableMoves = AvailableMoves::GetAvailableMoves(state, state.CurrentPlayer.Type);

    for (const auto& move : availableMoves)
    {
        auto params = Params { -10, 10 };
        auto copyState = state;
        copyState.MovePiece(move);
        value = MinimaxValue(copyState, depth, params);
        ratedMoves.insert({ value, move });
    }

    return ratedMoves;
}

double AlphaBeta::MinimaxValue(board::Checkerboard& state, int depth, Params params)
{
    auto availableMoves = AvailableMoves::GetAvailableMoves(state, state.CurrentPlayer.Type);

    if (TerminalTest(state, availableMoves, depth))
    {
        m_Nodes++;
        return m_EvalFunction->Evaluate(state, availableMoves, m_MoveCount);
    }
    else if (state.CurrentPlayer == m_Player)
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

double AlphaBeta::MaxValue(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth, Params params)
{
    for (const auto& move : availableMoves)
    {
        auto copyState = state;
        copyState.MovePiece(move);
        params.Alpha = std::max(params.Alpha, MinimaxValue(copyState, depth - 1, params));
        if (params.Alpha >= params.Beta)
        {
            break;
        }
    }

    return params.Alpha;
}

double AlphaBeta::MinValue(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth, Params params)
{
    for (const auto& move : availableMoves)
    {
        auto copyState = state;
        copyState.MovePiece(move);
        params.Beta = std::min(params.Beta, MinimaxValue(copyState, depth - 1, params));
        if (params.Alpha >= params.Beta)
        {
            break;
        }
    }

    return params.Beta;
}
