#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "../../DrawBoard/board.h"
#include "../../Utils/move.h"
#include "../../Utils/point.h"
#include <vector>

class MinMax
{
public:
    static Move GetMove(const board::Checkerboard& board, const std::vector<Move>& availableMoves);
};

#endif