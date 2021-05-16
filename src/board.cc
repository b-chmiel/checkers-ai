#include "board.h"
#include "constants.h"
#include <cmath>
#include <iostream>
#include <string>

using namespace board;

Checkerboard::Checkerboard()
{
    const int middleRow = constants::BOARD_HEIGHT / 2;

    auto currentPlayer = player::PlayerType::PLAYER2;
    for (auto i = 0; i < constants::BOARD_HEIGHT; i++) {
        if (i > middleRow) {
            currentPlayer = player::PlayerType::PLAYER1;
        }

        for (auto j = 0; j < constants::BOARD_WIDTH; j++) {
            if (i == middleRow || i == middleRow - 1) {
                Checkerboard::state[i][j] = piece::Piece(player::PlayerType::NONE, piece::PieceType::EMPTY);
            } else if (i % 2 == j % 2) {
                Checkerboard::state[i][j] = piece::Piece(player::PlayerType::NONE, piece::PieceType::EMPTY);
            } else {
                Checkerboard::state[i][j] = piece::Piece(currentPlayer, piece::PieceType::MAN);
            }
        }
    }
}

void Checkerboard::Show()
{
    const std::string cancelEffects = "\e[0m";
    const int height = constants::BOARD_HEIGHT;
    const int width = constants::BOARD_WIDTH;

    for (auto i = 0; i < height; i++) {
        printf("%s", GetFieldNumber(i).c_str());

        for (auto j = 0; j < width; j++) {
            printf("%s", GetFieldString(i, j).c_str());
        }

        printf("%s\n", cancelEffects.c_str());
    }

    PrintLettersBelow();
    printf("%s", cancelEffects.c_str());
}

std::string Checkerboard::GetFieldNumber(int i)
{
    const int height = constants::BOARD_HEIGHT;
    std::string result = std::to_string(height - i);
    result += " ";

    if (std::to_string(height - i).length() == 1) {
        result += " ";
    }

    return result;
}

std::string Checkerboard::GetFieldString(int i, int j)
{
    const std::string colorA = "\e[0;44;43m";
    const std::string colorB = "\e[0;30;44m";

    std::string field = GetFieldIcon(i, j);
    std::string color;

    if (i % 2 == j % 2) {
        color = colorA;
    } else {
        color = colorB;
    }

    return color + field;
}

std::string Checkerboard::GetFieldIcon(int i, int j)
{
    auto piece = Checkerboard::state[i][j];
    return piece.GetIcon();
}

void Checkerboard::PrintLettersBelow()
{
    char current = 'A';
    printf("   ");
    for (auto i = 0; i < constants::BOARD_WIDTH; i++) {
        printf(" %c ", current++);
    }
}

bool Checkerboard::Move(const std::vector<Position> path)
{
    Position last = path.at(0);

    for (const auto& current : path) {
        if (last == current) {
            continue;
        }

        if (IsLegalMove(last, current)) {
            MovePiece(last, current);
        } else {
            return false;
        }

        last = current;
    }

    if (IsPiecePromotion(last)) {
        PromotePiece(last);
    }

    Checkerboard::currentPlayer = player::GetAnotherPlayer(Checkerboard::currentPlayer);

    return true;
}

bool Checkerboard::IsLegalMove(const Position& from, const Position& to)
{
    auto startField = GetFieldPiece(from);
    auto endField = GetFieldPiece(to);

    if (startField.player != Checkerboard::currentPlayer || endField.player != player::NONE) {
        return false;
    }

    MoveType type = GetMoveType(from, to);

    if (type == MoveType::SHORT) {
        return ValidateShortMove(from, to);
    } else if (type == MoveType::LONG) {
        return ValidateLongMove(from, to);
    }

    return false;
}

piece::Piece Checkerboard::GetFieldPiece(const Position& position)
{
    return Checkerboard::state[position.y][position.x];
}

MoveType Checkerboard::GetMoveType(const Position& from, const Position& to)
{
    const int differenceHorizontal = std::abs(from.x - to.x);
    const int differenceVertical = std::abs(from.y - to.y);
    const int shortLenght = 1;
    const int longLenght = 2;

    if (differenceHorizontal != differenceVertical) {
        return MoveType::ILLEGAL;
    } else if (differenceHorizontal == shortLenght) {
        return MoveType::SHORT;
    } else if (differenceHorizontal == longLenght) {
        return MoveType::LONG;
    }

    return MoveType::ILLEGAL;
}

bool Checkerboard::ValidateShortMove(const Position& from, const Position& to)
{
    const int differenceVertical = from.y - to.y;

    if (differenceVertical > 0) {
        return Checkerboard::currentPlayer == player::PLAYER1;
    } else {
        return Checkerboard::currentPlayer == player::PLAYER2;
    }
}

bool Checkerboard::ValidateLongMove(const Position& from, const Position& to)
{
    auto x = (to.x + from.x) / 2;
    auto y = (to.y + from.y) / 2;
    auto interPiece = Checkerboard::state[y][x];

    if (interPiece.player == Checkerboard::currentPlayer || interPiece.player == player::PlayerType::NONE) {
        return false;
    }

    return true;
}

void Checkerboard::MovePiece(const Position& from, const Position& to)
{
    auto fieldStart = Checkerboard::state[from.y][from.x];
    Checkerboard::state[to.y][to.x] = std::move(fieldStart);
    Checkerboard::state[from.y][from.x].player = player::PlayerType::NONE;
    Checkerboard::state[from.y][from.x].type = piece::PieceType::EMPTY;
}

bool Checkerboard::IsPiecePromotion(const Position& position)
{
    auto piece = GetFieldPiece(position);

    if (piece.type == piece::KING)
        return false;

    return IsEndPositionForPlayer(position, piece.player);
}

bool Checkerboard::IsEndPositionForPlayer(const Position& position, player::PlayerType player)
{
    if (player == player::PLAYER2) {
        return position.y == constants::BOARD_HEIGHT - 1;
    }

    return position.y == 0;
}

void Checkerboard::PromotePiece(const Position& position)
{
    Checkerboard::state[position.y][position.x].type = piece::KING;
}