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
    static std::optional<Move> GetMove(const board::Checkerboard& board, const std::vector<Move>& availableMoves);

private:
    static Move ParseMove(const std::string& input);
};
#endif