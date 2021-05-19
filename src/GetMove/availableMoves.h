#ifndef AVAILABLE_MOVES_H
#define AVAILABLE_MOVES_H

#include "../DrawBoard/board.h"
#include "../Utils/player.h"
#include <vector>

class AvailableMoves
{
public:
    static std::vector<std::vector<Point>> GetAvailableMoves(const board::Checkerboard& board, player::PlayerType player);

private:
    static std::vector<std::vector<Point>> AddLongMoves(const Point& from, std::vector<Point> last, const board::Checkerboard&, player::PlayerType);
    static std::vector<std::vector<Point>> AddShortMoves(const Point& from, const board::Checkerboard&, player::PlayerType);
    static bool IsPointWithinBounds(const Point&);
    static bool IsCycle(const std::vector<Point>& path, const Point& point);
};

#endif