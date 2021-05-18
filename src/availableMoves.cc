#include "availableMoves.h"
#include "board.h"
#include "constants.h"
#include "player.h"
#include "point.h"
#include <algorithm>

struct PlayerMove
{
    Point from;
    Point to;
    player::PlayerType player;
};

std::vector<std::vector<Point>> AvailableMoves::GetAvailableMoves(const board::Checkerboard& board, player::PlayerType player)
{
    std::vector<std::vector<Point>> result;
    for (auto y = 0; y < constants::BOARD_HEIGHT; y++)
    {
        //search only in squares that contains piece
        for (auto x = 1 - y % 2; x < constants::BOARD_WIDTH; x += 2)
        {
            if (board.state[y][x].player == player)
            {
                auto from = Point { x, y };

                auto longMoves = AddLongMoves(from, { from }, board, player);
                auto shortMoves = AddShortMoves(from, board, player);

                result.insert(result.end(), longMoves.begin(), longMoves.end());
                result.insert(result.end(), shortMoves.begin(), shortMoves.end());
            }
        }
    }

    return result;
}

std::vector<std::vector<Point>> AvailableMoves::AddLongMoves(const Point& from, std::vector<Point> last, const board::Checkerboard& board, player::PlayerType player)
{
    Point to;
    std::vector<std::vector<Point>> result;

    for (auto directionY = -2; directionY <= 2; directionY += 4)
    {
        for (auto directionX = -2; directionX <= 2; directionX += 4)
        {
            to.x = from.x + directionX;
            to.y = from.y + directionY;

            if (!IsPointWithinBounds(to) || IsCycle(last, to))
            {
                continue;
            }

            if (board.IsMoveValid(from, to, player))
            {
                last.push_back(to);
                result.push_back(last);
                auto longer = AddLongMoves(to, last, board, player);
                last.pop_back();
                result.insert(result.end(), longer.begin(), longer.end());
            }
        }
    }

    return result;
}

bool AvailableMoves::IsCycle(const std::vector<Point>& path, const Point& point)
{
    return std::count(path.begin(), path.end(), point) > 1;
}

std::vector<std::vector<Point>> AvailableMoves::AddShortMoves(const Point& from, const board::Checkerboard& board, player::PlayerType player)
{
    Point to;
    std::vector<std::vector<Point>> result;

    for (auto directionY = -1; directionY <= 1; directionY += 2)
    {
        for (auto directionX = -1; directionX <= 1; directionX += 2)
        {
            to.x = from.x + directionX;
            to.y = from.y + directionY;

            if (!IsPointWithinBounds(to))
            {
                continue;
            }

            if (board.IsMoveValid(from, to, player))
            {
                result.push_back({ Point { from }, Point { to } });
            }
        }
    }

    return result;
}

bool AvailableMoves::IsPointWithinBounds(const Point& point)
{
    return point.x >= 0 && point.y >= 0 && point.x < constants::BOARD_WIDTH && point.y < constants::BOARD_HEIGHT;
}