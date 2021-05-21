#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "../../DrawBoard/board.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include "ratedMove.h"
#include <optional>
#include <vector>

namespace minmax
{
class MinMax
{
public:
    MinMax(int depth);
    std::optional<Move> GetMove(board::Checkerboard& board);

private:
    int m_Depth;

    double MinimaxValue(board::Checkerboard& state, const board::Checkerboard& game, int depth);
    int GetWinnerPayoff(const player::Player& player, const board::Checkerboard& game);
    rated_move::rated_move_set MinMaxDecision(board::Checkerboard& board, int depth);
};
}

#endif