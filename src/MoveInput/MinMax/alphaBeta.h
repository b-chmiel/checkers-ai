#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include "../../Board/board.h"
#include "../../Utils/move.h"
#include "../../Utils/player.h"
#include "../moveInput.h"
#include "EvaluationFunction/evaluationFunction.h"
#include "ratedMove.h"
#include <memory>
#include <optional>
#include <vector>

namespace alpha_beta
{
struct Params
{
    double Alpha;
    double Beta;
};

class AlphaBeta : public MoveInput
{
public:
    AlphaBeta(int depth, std::shared_ptr<EvaluationFunction>);
    std::optional<Move> ProcessMove(const board::Checkerboard& board) override;
    ~AlphaBeta() = default;

private:
    int m_Depth;
    int m_Nodes;
    player::Player m_Player;
    std::shared_ptr<EvaluationFunction> m_EvalFunction;

    rated_move::rated_move_set MinMaxDecision(const board::Checkerboard& board, int depth);
    double MinimaxValue(board::Checkerboard& state, int depth, Params params);
    bool TerminalTest(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth);

    double MaxValue(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth, Params params);
    double MinValue(board::Checkerboard& state, const std::vector<Move>& availableMoves, int depth, Params params);
};

}
#endif
