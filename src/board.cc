#include "board.h"
#include "constants.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace board;

Checkerboard::Checkerboard()
{
    const int middleRow = constants::BOARD_HEIGHT / 2;

    auto currentPlayer = player::PlayerType::PLAYER2;
    for (auto y = 0; y < constants::BOARD_HEIGHT; y++)
    {
        if (y > middleRow)
        {
            currentPlayer = player::PlayerType::PLAYER1;
        }

        for (auto x = 0; x < constants::BOARD_WIDTH; x++)
        {
            if (IsInitiallyEmpty(Point { x, y }, middleRow))
            {
                Checkerboard::state[y][x] = piece::Piece();
            }
            else
            {
                Checkerboard::state[y][x] = piece::Piece(currentPlayer, piece::PieceType::MAN);
                Checkerboard::piecesAlive[currentPlayer]++;
            }
        }
    }
}

bool Checkerboard::IsInitiallyEmpty(const Point& point, int middleRow)
{
    auto isMiddleRow = point.y == middleRow || point.y == middleRow - 1;
    auto isOnDiagonals = point.y % 2 == point.x % 2;

    return isMiddleRow || isOnDiagonals;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
void Checkerboard::Show() const
{
    const std::string cancelEffects = "\e[0m";
    const int height = constants::BOARD_HEIGHT;
    const int width = constants::BOARD_WIDTH;

    for (auto y = 0; y < height; y++)
    {
        printf("%s", GetFieldNumber(y).c_str());

        for (auto x = 0; x < width; x++)
        {
            printf("%s", GetFieldString(y, x).c_str());
        }

        printf("%s\n", cancelEffects.c_str());
    }

    PrintLettersBelow();
    printf("%s", cancelEffects.c_str());
}
#pragma GCC diagnostic pop

std::string Checkerboard::GetFieldNumber(int y) const
{
    const int height = constants::BOARD_HEIGHT;
    std::string result = std::to_string(height - y);
    result += " ";

    if (std::to_string(height - y).length() == 1)
    {
        result += " ";
    }

    return result;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
std::string Checkerboard::GetFieldString(int y, int x) const
{
    const std::string colorA = "\e[0;44;43m";
    const std::string colorB = "\e[0;30;44m";

    std::string field = GetFieldIcon(y, x);
    std::string color;

    if (y % 2 == x % 2)
    {
        color = colorA;
    }
    else
    {
        color = colorB;
    }

    return color + field;
}
#pragma GCC diagnostic pop

std::string Checkerboard::GetFieldIcon(int y, int x) const
{
    auto piece = Checkerboard::state[y][x];
    return piece.GetIcon();
}

void Checkerboard::PrintLettersBelow() const
{
    char current = 'A';
    printf("   ");
    for (auto i = 0; i < constants::BOARD_WIDTH; i++)
    {
        printf(" %c ", current++);
    }
}

bool Checkerboard::IsMoveValid(const Point& from, const Point& to, player::PlayerType) const
{
    auto startField = Checkerboard::state[from.y][from.x];
    auto endField = Checkerboard::state[to.y][to.x];

    if (endField.player != player::NONE)
    {
        return false;
    }

    MoveType type = GetMoveType(from, to);

    if (type == MoveType::SHORT)
    {
        if (startField.type == piece::KING)
        {
            return true;
        }

        return ValidateShortMove(from, to);
    }
    else if (type == MoveType::LONG)
    {
        return ValidateLongMove(from, to);
    }

    return false;
}

MoveType Checkerboard::GetMoveType(const Point& from, const Point& to) const
{
    const int differenceHorizontal = std::abs(from.x - to.x);
    const int shortLength = 1;
    const int longLength = 2;

    if (differenceHorizontal == shortLength)
    {
        return MoveType::SHORT;
    }
    else if (differenceHorizontal == longLength)
    {
        return MoveType::LONG;
    }

    return MoveType::ILLEGAL;
}

bool Checkerboard::ValidateShortMove(const Point& from, const Point& to) const
{
    const int differenceVertical = from.y - to.y;

    if (differenceVertical > 0)
    {
        return Checkerboard::currentPlayer == player::PLAYER1;
    }
    else
    {
        return Checkerboard::currentPlayer == player::PLAYER2;
    }
}

bool Checkerboard::ValidateLongMove(const Point& from, const Point& to) const
{
    auto x = (to.x + from.x) / 2;
    auto y = (to.y + from.y) / 2;
    auto interPiece = Checkerboard::state[y][x];

    if (interPiece.player == Checkerboard::currentPlayer || interPiece.player == player::PlayerType::NONE)
    {
        return false;
    }

    return true;
}

void Checkerboard::Move(const std::vector<Point>& path)
{
    auto last = path.at(0);

    for (const auto& current : path)
    {
        if (last == current)
        {
            continue;
        }

        MoveType move = GetMoveType(last, current);
        if (move == MoveType::ILLEGAL)
        {
            throw "Critical error";
        }

        ChangePositionOfPiece(last, current, move);

        last = current;
    }

    if (IsPiecePromotion(last))
    {
        PromotePiece(last);
    }

    Checkerboard::currentPlayer = player::Player::GetAnotherPlayer(Checkerboard::currentPlayer);
}

void Checkerboard::ChangePositionOfPiece(const Point& from, const Point& to, MoveType move)
{
    auto fieldStart = Checkerboard::state[from.y][from.x];
    Checkerboard::state[to.y][to.x] = std::move(fieldStart);
    Checkerboard::state[from.y][from.x].player = player::PlayerType::NONE;
    Checkerboard::state[from.y][from.x].type = piece::PieceType::EMPTY;

    if (move == MoveType::LONG)
    {
        Capture(from, to);
    }
}

void Checkerboard::Capture(const Point& from, const Point& to)
{
    auto x = (from.x + to.x) / 2;
    auto y = (from.y + to.y) / 2;

    piece::Piece* captured = &Checkerboard::state[y][x];

    Checkerboard::piecesAlive[captured->player]--;
    captured->player = player::NONE;
    captured->type = piece::EMPTY;
}

bool Checkerboard::IsPiecePromotion(const Point& position) const
{
    auto piece = GetFieldPiece(position);

    if (piece.type == piece::KING)
    {
        return false;
    }

    return IsEndPositionForPlayer(position, piece.player);
}

bool Checkerboard::IsEndPositionForPlayer(const Point& position, player::PlayerType player) const
{
    if (player == player::PLAYER2)
    {
        return position.y == constants::BOARD_HEIGHT - 1;
    }

    return position.y == 0;
}

void Checkerboard::PromotePiece(const Point& position)
{
    Checkerboard::state[position.y][position.x].type = piece::KING;
}

bool Checkerboard::IsGameCompleted()
{
    return (Checkerboard::piecesAlive[player::PLAYER1] == 0 || Checkerboard::piecesAlive[player::PLAYER2] == 0);
}

piece::Piece Checkerboard::GetFieldPiece(const Point& position) const
{
    return Checkerboard::state[position.y][position.x];
}