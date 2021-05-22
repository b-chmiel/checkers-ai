#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "../../Board/board.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include "../moveInput.h"
#include "EvaluationFunction/evaluationFunction.h"
#include "ratedMove.h"
#include <memory>
#include <optional>
#include <vector>

namespace minmax
{
class MinMax : public MoveInput
{
public:
    MinMax(int depth, std::shared_ptr<EvaluationFunction>);
    std::optional<Move> ProcessMove(const board::Checkerboard& board, int moveCount) override;
    ~MinMax() = default;

private:
    int m_Depth;
    int m_Nodes;
    int m_MoveCount;
    std::shared_ptr<EvaluationFunction> m_EvalFunction;

    rated_move::rated_move_set MinMaxDecision(const board::Checkerboard& board, int depth);
    double MinimaxValue(board::Checkerboard& state, const board::Checkerboard& game, int depth);
};
}

#endif