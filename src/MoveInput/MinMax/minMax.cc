#include "minMax.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include "../availableMoves.h"
#include "EvaluationFunction/evaluationFunction.h"
#include "ratedMove.h"
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

using namespace minmax;

MinMax::MinMax(int depth, std::shared_ptr<EvaluationFunction> eval)
    : m_Depth(depth)
    , m_Nodes(0)
    , m_EvalFunction(eval)
{
}

std::optional<Move> MinMax::ProcessMove(const board::Checkerboard& board, int moveCount)
{
    m_Nodes = 0;
    m_MoveCount = moveCount;

    auto result = MinMaxDecision(board, m_Depth - 1);

    // std::cout << "Nodes: " << m_Nodes << std::endl;
    if (result.size() == 0)
    {
        return std::nullopt;
    }

    return (*result.rbegin()).Move;
}

rated_move::rated_move_set MinMax::MinMaxDecision(const board::Checkerboard& state, int depth)
{
    double value;
    rated_move::rated_move_set ratedMoves(rated_move::MoveComparison {});
    auto availableMoves = AvailableMoves::GetAvailableMoves(state, state.CurrentPlayer.Type);

    for (const auto& move : availableMoves)
    {
        auto boardCopy = state;
        boardCopy.MovePiece(move);
        value = MinimaxValue(boardCopy, state, depth);
        ratedMoves.insert({ value, move });
    }

    return ratedMoves;
}

double MinMax::MinimaxValue(board::Checkerboard& state, const board::Checkerboard& game, int depth)
{
    auto availableMoves = AvailableMoves::GetAvailableMoves(state, state.CurrentPlayer.Type);

    if (state.IsGameCompleted() || availableMoves.size() == 0 || depth == 0)
    {
        m_Nodes++;
        return m_EvalFunction->Evaluate(state, availableMoves, m_MoveCount);
    }
    else if (state.CurrentPlayer.Type == game.CurrentPlayer.Type)
    {
        return (*MinMaxDecision(state, depth - 1).rbegin()).Key;
    }
    else
    {
        return (*MinMaxDecision(state, depth - 1).begin()).Key;
    }
}