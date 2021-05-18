#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "board.h"
#include "point.h"
#include <string>
#include <vector>

class UserInput
{
public:
    static std::optional<std::vector<Point>> GetUserInput(const board::Checkerboard& board, const std::vector<std::vector<Point>>& availableMoves);

private:
    static std::vector<Point> ParsePath(std::string input);
};
#endif