#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "../../DrawBoard/board.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include <optional>
#include <string>
#include <vector>

class UserInput
{
public:
    std::optional<Move> ProcessMove(const board::Checkerboard& board) const;

private:
    Move ParseMove(const std::string& input) const;
};
#endif