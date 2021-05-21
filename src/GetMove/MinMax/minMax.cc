#include "minMax.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include "../availableMoves.h"
#include "EvaluationFunction/evaluateOne.h"
#include "ratedMove.h"
#include <optional>
#include <stdexcept>
#include <vector>

using namespace minmax;

MinMax::MinMax(int depth)
    : m_Depth(depth)
{
}

std::optional<Move> MinMax::GetMove(board::Checkerboard& board)
{
    auto result = MinMaxDecision(board, m_Depth);

    if (result.size() == 0)
    {
        return std::nullopt;
    }

    return (*result.rbegin()).Move;
}

rated_move::rated_move_set MinMax::MinMaxDecision(board::Checkerboard& state, int depth)
{
    rated_move::rated_move_set ratedMoves(rated_move::MoveComparison {});
    double value;
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

    depth--;
    if (state.IsGameCompleted() || availableMoves.size() == 0 || depth == 0)
    {
        EvaluateOne e;
        return e.Evaluate(state);
    }
    else if (state.CurrentPlayer.Type == game.CurrentPlayer.Type)
    {
        return (*MinMaxDecision(state, depth).rbegin()).Key;
    }
    else
    {
        return (*MinMaxDecision(state, depth).begin()).Key;
    }
}

int MinMax::GetWinnerPayoff(const player::Player& player, const board::Checkerboard& game)
{
    return player == game.CurrentPlayer ? -1 : 1;
}