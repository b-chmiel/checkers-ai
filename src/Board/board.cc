#include "board.h"
#include "constants.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace board;

Checkerboard::Checkerboard()
{
    constexpr int middleRow = constants::BOARD_HEIGHT / 2;

    auto currentPlayer = player::Player(player::PlayerType::PLAYER2);

    for (auto y = 0; y < constants::BOARD_HEIGHT; y++)
    {
        if (y > middleRow)
        {
            currentPlayer.Type = player::PlayerType::PLAYER1;
        }

        for (auto x = 0; x < constants::BOARD_WIDTH; x++)
        {
            if (IsInitiallyEmpty(Point { x, y }, middleRow))
            {
                Checkerboard::State[y][x] = piece::Piece();
            }
            else
            {
                Checkerboard::State[y][x] = piece::Piece(currentPlayer, piece::PieceType::MAN);
                Checkerboard::m_PiecesAlive[currentPlayer.Type]++;
            }
        }
    }
}

bool Checkerboard::IsInitiallyEmpty(const Point& point, int middleRow)
{
    auto isMiddleRow = point.Y == middleRow || point.Y == middleRow - 1;
    auto isOnDiagonals = point.Y % 2 == point.X % 2;

    return isMiddleRow || isOnDiagonals;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
void Checkerboard::Show() const
{
    const std::string cancelEffects = "\e[0m";
    const int height = constants::BOARD_HEIGHT;
    const int width = constants::BOARD_WIDTH;

    printf("\n");

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
    auto piece = Checkerboard::State[y][x];
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
    auto startField = Checkerboard::State[from.Y][from.X];
    auto endField = Checkerboard::State[to.Y][to.X];

    if (endField.Player.Type != player::NONE)
    {
        return false;
    }

    PieceMoveType type = GetMoveType(from, to);

    if (type == PieceMoveType::SHORT)
    {
        if (startField.Type == piece::KING)
        {
            return true;
        }

        return ValidateShortMove(from, to);
    }
    else if (type == PieceMoveType::LONG)
    {
        return ValidateLongMove(from, to);
    }

    return false;
}

PieceMoveType Checkerboard::GetMoveType(const Point& from, const Point& to) const
{
    const int differenceHorizontal = std::abs(from.X - to.X);
    const int shortLength = 1;
    const int longLength = 2;

    if (differenceHorizontal == shortLength)
    {
        return PieceMoveType::SHORT;
    }
    else if (differenceHorizontal == longLength)
    {
        return PieceMoveType::LONG;
    }

    return PieceMoveType::ILLEGAL;
}

bool Checkerboard::ValidateShortMove(const Point& from, const Point& to) const
{
    const int differenceVertical = from.Y - to.Y;

    if (differenceVertical > 0)
    {
        return Checkerboard::CurrentPlayer.Type == player::PLAYER1;
    }
    else
    {
        return Checkerboard::CurrentPlayer.Type == player::PLAYER2;
    }
}

bool Checkerboard::ValidateLongMove(const Point& from, const Point& to) const
{
    auto x = (to.X + from.X) / 2;
    auto y = (to.Y + from.Y) / 2;
    auto interPiece = Checkerboard::State[y][x];

    if (interPiece.Player == Checkerboard::CurrentPlayer || interPiece.Player == player::PlayerType::NONE)
    {
        return false;
    }

    return true;
}

void Checkerboard::MovePiece(const Move& path)
{
    auto last = path.Path.at(0);

    for (const auto& current : path.Path)
    {
        if (last == current)
        {
            continue;
        }

        PieceMoveType move = GetMoveType(last, current);
        if (move == PieceMoveType::ILLEGAL)
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

    Checkerboard::CurrentPlayer = Checkerboard::CurrentPlayer.GetAnotherPlayer();
}

void Checkerboard::ChangePositionOfPiece(const Point& from, const Point& to, PieceMoveType move)
{
    auto fieldStart = Checkerboard::State[from.Y][from.X];
    Checkerboard::State[to.Y][to.X] = std::move(fieldStart);
    Checkerboard::State[from.Y][from.X].Player = player::PlayerType::NONE;
    Checkerboard::State[from.Y][from.X].Type = piece::PieceType::EMPTY;

    if (move == PieceMoveType::LONG)
    {
        Capture(from, to);
    }
}

void Checkerboard::Capture(const Point& from, const Point& to)
{
    auto x = (from.X + to.X) / 2;
    auto y = (from.Y + to.Y) / 2;

    piece::Piece* captured = &Checkerboard::State[y][x];

    Checkerboard::m_PiecesAlive[captured->Player.Type]--;
    captured->Player = player::NONE;
    captured->Type = piece::EMPTY;
}

bool Checkerboard::IsPiecePromotion(const Point& position) const
{
    auto piece = GetFieldPiece(position);

    if (piece.Type == piece::KING)
    {
        return false;
    }

    return IsEndPositionForPlayer(position, piece.Player.Type);
}

bool Checkerboard::IsEndPositionForPlayer(const Point& position, player::PlayerType player) const
{
    if (player == player::PLAYER2)
    {
        return position.Y == constants::BOARD_HEIGHT - 1;
    }

    return position.Y == 0;
}

void Checkerboard::PromotePiece(const Point& position)
{
    Checkerboard::State[position.Y][position.X].Type = piece::KING;
}

bool Checkerboard::IsGameCompleted()
{
    return (Checkerboard::m_PiecesAlive[player::PLAYER1] == 0 || Checkerboard::m_PiecesAlive[player::PLAYER2] == 0);
}

piece::Piece Checkerboard::GetFieldPiece(const Point& position) const
{
    return Checkerboard::State[position.Y][position.X];
}

player::PlayerType Checkerboard::GetWinner()
{
    int piecesPlayer1 = Checkerboard::m_PiecesAlive[player::PLAYER1];
    int piecesPlayer2 = Checkerboard::m_PiecesAlive[player::PLAYER2];

    return piecesPlayer1 > piecesPlayer2 ? player::PlayerType::PLAYER1 : player::PlayerType::PLAYER2;
}