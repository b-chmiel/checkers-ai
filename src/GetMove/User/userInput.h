#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "../../DrawBoard/board.h"
#include "../../Utils/point.h"
#include <optional>
#include <string>
#include <vector>

class UserInput
{
public:
    static std::optional<std::vector<Point>> GetMove(const board::Checkerboard& board, const std::vector<std::vector<Point>>& availableMoves);

private:
    static std::vector<Point> ParsePath(std::string input);
};
#endif