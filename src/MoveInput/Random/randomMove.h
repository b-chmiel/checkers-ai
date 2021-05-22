#ifndef RANDOM_MOVE_H
#define RANDOM_MOVE_H

#include "../../Board/board.h"
#include "../../Utils/move.h"
#include "../moveInput.h"
#include <optional>

class RandomMove : public MoveInput
{
public:
    std::optional<Move> ProcessMove(const board::Checkerboard& board) override;
};
#endif
