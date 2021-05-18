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
                Checkerboard::m_State[y][x] = piece::Piece();
            }
            else
            {
                Checkerboard::m_State[y][x] = piece::Piece(currentPlayer, piece::PieceType::MAN);
                Checkerboard::piecesAlive[currentPlayer]++;
            }
        }
    }
}

bool Checkerboard::IsInitiallyEmpty(const Point& point, int middleRow)
{
    auto isMiddleRow = point.m_Y == middleRow || point.m_Y == middleRow - 1;
    auto isOnDiagonals = point.m_Y % 2 == point.m_X % 2;

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
    auto piece = Checkerboard::m_State[y][x];
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
    auto startField = Checkerboard::m_State[from.m_Y][from.m_X];
    auto endField = Checkerboard::m_State[to.m_Y][to.m_X];

    if (endField.m_Player != player::NONE)
    {
        return false;
    }

    MoveType type = GetMoveType(from, to);

    if (type == MoveType::SHORT)
    {
        if (startField.m_Type == piece::KING)
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
    const int differenceHorizontal = std::abs(from.m_X - to.m_X);
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
    const int differenceVertical = from.m_Y - to.m_Y;

    if (differenceVertical > 0)
    {
        return Checkerboard::m_CurrentPlayer == player::PLAYER1;
    }
    else
    {
        return Checkerboard::m_CurrentPlayer == player::PLAYER2;
    }
}

bool Checkerboard::ValidateLongMove(const Point& from, const Point& to) const
{
    auto x = (to.m_X + from.m_X) / 2;
    auto y = (to.m_Y + from.m_Y) / 2;
    auto interPiece = Checkerboard::m_State[y][x];

    if (interPiece.m_Player == Checkerboard::m_CurrentPlayer || interPiece.m_Player == player::PlayerType::NONE)
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

    Checkerboard::m_CurrentPlayer = player::Player::GetAnotherPlayer(Checkerboard::m_CurrentPlayer);
}

void Checkerboard::ChangePositionOfPiece(const Point& from, const Point& to, MoveType move)
{
    auto fieldStart = Checkerboard::m_State[from.m_Y][from.m_X];
    Checkerboard::m_State[to.m_Y][to.m_X] = std::move(fieldStart);
    Checkerboard::m_State[from.m_Y][from.m_X].m_Player = player::PlayerType::NONE;
    Checkerboard::m_State[from.m_Y][from.m_X].m_Type = piece::PieceType::EMPTY;

    if (move == MoveType::LONG)
    {
        Capture(from, to);
    }
}

void Checkerboard::Capture(const Point& from, const Point& to)
{
    auto x = (from.m_X + to.m_X) / 2;
    auto y = (from.m_Y + to.m_Y) / 2;

    piece::Piece* captured = &Checkerboard::m_State[y][x];

    Checkerboard::piecesAlive[captured->m_Player]--;
    captured->m_Player = player::NONE;
    captured->m_Type = piece::EMPTY;
}

bool Checkerboard::IsPiecePromotion(const Point& position) const
{
    auto piece = GetFieldPiece(position);

    if (piece.m_Type == piece::KING)
    {
        return false;
    }

    return IsEndPositionForPlayer(position, piece.m_Player);
}

bool Checkerboard::IsEndPositionForPlayer(const Point& position, player::PlayerType player) const
{
    if (player == player::PLAYER2)
    {
        return position.m_Y == constants::BOARD_HEIGHT - 1;
    }

    return position.m_Y == 0;
}

void Checkerboard::PromotePiece(const Point& position)
{
    Checkerboard::m_State[position.m_Y][position.m_X].m_Type = piece::KING;
}

bool Checkerboard::IsGameCompleted()
{
    return (Checkerboard::piecesAlive[player::PLAYER1] == 0 || Checkerboard::piecesAlive[player::PLAYER2] == 0);
}

piece::Piece Checkerboard::GetFieldPiece(const Point& position) const
{
    return Checkerboard::m_State[position.m_Y][position.m_X];
}