#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "../../Board/board.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include "../moveInput.h"
#include "ratedMove.h"
#include <optional>
#include <vector>

namespace minmax
{
class MinMax : public MoveInput
{
public:
    MinMax(int depth);
    std::optional<Move> ProcessMove(const board::Checkerboard& board) override;

private:
    int m_Depth;
    int m_Nodes;

    rated_move::rated_move_set MinMaxDecision(const board::Checkerboard& board, int depth);
    double MinimaxValue(board::Checkerboard& state, const board::Checkerboard& game, int depth);
};
}

#endif