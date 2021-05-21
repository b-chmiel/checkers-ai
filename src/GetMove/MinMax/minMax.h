#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "../../DrawBoard/board.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include <vector>

namespace minmax
{
struct RatedMove
{
    double Key;
    Move Move;
};

struct MoveComparison final
{
    inline bool operator()(const RatedMove& left, const RatedMove& right) const
    {
        return left.Key < right.Key;
    }
};
class MinMax
{
public:
    static Move GetMove(board::Checkerboard& board, const std::vector<Move>& availableMoves);

private:
    static const int m_Depth = 3;
    static double MinimaxValue(board::Checkerboard& state, const board::Checkerboard& game, int depth);

    static int GetWinnerPayoff(const player::Player& player, const board::Checkerboard& game);
    static std::set<RatedMove, MoveComparison> MinMaxDecision(board::Checkerboard& board, const std::vector<Move>& availableMoves, int depth);
};
}

#endif