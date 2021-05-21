#include "availableMoves.h"
#include "../DrawBoard/board.h"
#include "../DrawBoard/constants.h"
#include "../Utils/move.h"
#include "../Utils/player.h"
#include "../Utils/point.h"
#include <algorithm>

struct PlayerMove
{
    Point from;
    Point to;
    player::PlayerType player;
};

std::vector<Move> AvailableMoves::GetAvailableMoves(const board::Checkerboard& board, player::PlayerType player)
{
    std::vector<Move> result;
    for (auto y = 0; y < constants::BOARD_HEIGHT; y++)
    {
        //search only in squares that contains piece
        for (auto x = 1 - y % 2; x < constants::BOARD_WIDTH; x += 2)
        {
            if (board.State[y][x].Player == player)
            {
                auto from = Point { x, y };

                auto longMoves = AddLongMoves(from, Move(from), board, player);
                auto shortMoves = AddShortMoves(from, board, player);

                result.insert(result.end(), longMoves.begin(), longMoves.end());
                result.insert(result.end(), shortMoves.begin(), shortMoves.end());
            }
        }
    }

    return result;
}

std::vector<Move> AvailableMoves::AddLongMoves(const Point& from, Move last, const board::Checkerboard& board, player::PlayerType player)
{
    Point to;
    std::vector<Move> result;

    for (auto directionY = -2; directionY <= 2; directionY += 4)
    {
        for (auto directionX = -2; directionX <= 2; directionX += 4)
        {
            to.X = from.X + directionX;
            to.Y = from.Y + directionY;

            if (!IsPointWithinBounds(to) || IsCycle(last, to))
            {
                continue;
            }

            if (board.IsMoveValid(from, to, player))
            {
                last.Path.push_back(to);
                result.push_back(last);
                auto longer = AddLongMoves(to, last, board, player);
                last.Path.pop_back();
                result.insert(result.end(), longer.begin(), longer.end());
            }
        }
    }

    return result;
}

inline bool AvailableMoves::IsCycle(const Move& move, const Point& point)
{
    return std::count(move.Path.begin(), move.Path.end(), point) > 1;
}

std::vector<Move> AvailableMoves::AddShortMoves(const Point& from, const board::Checkerboard& board, player::PlayerType player)
{
    Point to;
    std::vector<Move> result;

    for (auto directionY = -1; directionY <= 1; directionY += 2)
    {
        for (auto directionX = -1; directionX <= 1; directionX += 2)
        {
            to.X = from.X + directionX;
            to.Y = from.Y + directionY;

            if (!IsPointWithinBounds(to))
            {
                continue;
            }

            if (board.IsMoveValid(from, to, player))
            {
                result.push_back(Move({ from, to }));
            }
        }
    }

    return result;
}

inline bool AvailableMoves::IsPointWithinBounds(const Point& point)
{
    return point.X >= 0 && point.Y >= 0 && point.X < constants::BOARD_WIDTH && point.Y < constants::BOARD_HEIGHT;
}