#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include "../../DrawBoard/board.h"
#include "../../Utils/move.h"
#include "ratedMove.h"
#include <optional>
#include <vector>

namespace alpha_beta
{
struct Params
{
    double Alpha;
    double Beta;
};

class AlphaBeta
{
public:
    AlphaBeta(int depth);
    std::optional<Move> GetMove(board::Checkerboard& board);

private:
    int m_Depth;

    rated_move::rated_move_set MinMaxDecision(board::Checkerboard& board, int depth);
    double MinimaxValue(board::Checkerboard& state, bool isMaximizingPlayer, int depth, Params& params);
    bool TerminalTest(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth);

    double MaxValue(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth, Params& params);
    double MinValue(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth, Params& params);
};

}
#endif
