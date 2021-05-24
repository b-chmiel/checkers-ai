#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "../../Board/board.h"
#include "../../Utils/move.h"
#include "../MinMax/EvaluationFunction/evaluationFunction.h"
#include "../moveInput.h"
#include <memory>
#include <optional>
#include <string>

class UserInput : public MoveInput
{
public:
    UserInput(int, std::shared_ptr<EvaluationFunction>) {};
    std::optional<Move> ProcessMove(const board::Checkerboard& board, int moveCount) override;
    ~UserInput() = default;

private:
    Move ParseMove(const std::string& input) const;
};
#endif