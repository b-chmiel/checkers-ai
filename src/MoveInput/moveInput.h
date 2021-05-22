#ifndef GET_MOVE_H
#define GET_MOVE_H

#include "../Board/board.h"
#include "../Utils/move.h"
#include <optional>

class MoveInput
{
public:
    virtual std::optional<Move> ProcessMove(const board::Checkerboard&) = 0;
};
#endif
