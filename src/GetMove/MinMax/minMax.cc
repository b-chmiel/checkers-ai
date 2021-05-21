#include "minMax.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include "../availableMoves.h"
#include "EvaluationFunction/evaluateOne.h"
#include <vector>

using namespace minmax;

Move MinMax::GetMove(board::Checkerboard& board, const std::vector<Move>& availableMoves)
{
    const int depth = 3;
    auto result = MinMaxDecision(board, availableMoves, depth);

    return (*result.rbegin()).Move;
}

std::set<RatedMove, MoveComparison>
MinMax::MinMaxDecision(board::Checkerboard& board, const std::vector<Move>& availableMoves, int depth)
{
    std::set<RatedMove, MoveComparison> ratedMoves(MoveComparison {});
    double value;

    for (const auto& move : availableMoves)
    {
        auto boardCopy = board;
        boardCopy.MovePiece(move);
        value = MinimaxValue(boardCopy, board, depth);
        ratedMoves.insert({ value, move });
    }

    return ratedMoves;
}

double MinMax::MinimaxValue(board::Checkerboard& state, const board::Checkerboard& game, int depth)
{
    auto availableMoves = AvailableMoves::GetAvailableMoves(state, state.CurrentPlayer.Type);

    depth--;
    if (depth < 0)
    {
        EvaluateOne e;
        return e.Evaluate(state);
    }
    if (state.IsGameCompleted() || availableMoves.size() == 0)
    {
        return GetWinnerPayoff(state.CurrentPlayer, game);
    }
    else if (state.CurrentPlayer.Type == game.CurrentPlayer.Type)
    {
        return (*MinMaxDecision(state, availableMoves, depth).rbegin()).Key;
    }
    else
    {
        return (*MinMaxDecision(state, availableMoves, depth).begin()).Key;
    }
}

int MinMax::GetWinnerPayoff(const player::Player& player, const board::Checkerboard& game)
{
    return player == game.CurrentPlayer ? -1 : 1;
}