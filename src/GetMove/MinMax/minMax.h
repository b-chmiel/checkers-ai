#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "../../DrawBoard/board.h"
#include "../../Utils/point.h"
#include <vector>

class MinMax
{
public:
    static std::vector<Point> GetMove(const board::Checkerboard& board, const std::vector<std::vector<Point>>& availableMoves);
};

#endif