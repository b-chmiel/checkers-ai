#ifndef AVAILABLE_MOVES_H
#define AVAILABLE_MOVES_H

#include "../Board/board.h"
#include "../Utils/move.h"
#include "../Utils/player.h"
#include <vector>

class AvailableMoves
{
public:
    static std::vector<Move> GetAvailableMoves(const board::Checkerboard& board, player::PlayerType player);

private:
    static std::vector<Move> AddLongMoves(const Point& from, Move last, const board::Checkerboard&, player::PlayerType);
    static std::vector<Move> AddShortMoves(const Point& from, const board::Checkerboard&, player::PlayerType);
    static bool IsPointWithinBounds(const Point&);
    static bool IsCycle(const Move& path, const Point& point);
};

#endif