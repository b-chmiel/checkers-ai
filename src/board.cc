#include "board.h"
#include "constants.h"
#include <iostream>
#include <string>

using namespace board;

Piece::Piece(const Player player, const PieceType type)
{
    Piece::player = player;
    Piece::type = type;
}

Checkerboard::Checkerboard()
{
    auto currentPlayer = Player::PLAYER2;
    for (auto i = 0; i < constants::BOARD_HEIGHT; i++) {
        if (i > 3) {
            currentPlayer = Player::PLAYER1;
        }

        for (auto j = 0; j < constants::BOARD_WIDTH; j++) {
            if (i == 3 || i == 4) {
                Checkerboard::state[i][j] = Piece(Player::NONE, PieceType::EMPTY);
            } else if (i % 2 == j % 2) {
                Checkerboard::state[i][j] = Piece(Player::NONE, PieceType::EMPTY);
            } else {
                Checkerboard::state[i][j] = Piece(currentPlayer, PieceType::MAN);
            }
        }
    }
}

void Checkerboard::Show()
{
    const char* colorA = "\e[0;44;43m";
    const char* colorB = "\e[0;30;44m";
    const char* cancelEffects = "\e[0m";
    const int height = constants::BOARD_HEIGHT;
    const int width = constants::BOARD_WIDTH;

    for (auto i = 0; i < height; i++) {
        printf("%d ", height - i);
        if (i != 0) {
            printf(" ");
        }
        for (auto j = 0; j < width; j++) {
            const char* field = GetFieldIcon(i, j);

            if (i % 2 == j % 2) {
                printf("%s", colorA);
            } else {
                printf("%s", colorB);
            }

            printf("%s", field);
        }
        printf("%s\n", cancelEffects);
    }

    PrintLettersBelow();
    printf("%s", cancelEffects);
}

enum FieldType {
    NONE,
    PLAYER1,
    PLAYER2,
    PLAYER1_KING,
    PLAYER2_KING
};

const char* Checkerboard::GetFieldIcon(int i, int j)
{
    const char* icons[5] = { "   ", " ⛀ ", " ⛂ ", " ⛁ ", " ⛃ " };
    auto fieldState = Checkerboard::state[i][j];
    FieldType type;

    if (fieldState.player == Player::NONE) {
        type = FieldType::NONE;
    } else if (fieldState.player == Player::PLAYER1) {
        if (fieldState.type == PieceType::MAN) {
            type = FieldType::PLAYER1;
        } else {
            type = FieldType::PLAYER1_KING;
        }
    } else {
        if (fieldState.type == PieceType::MAN) {
            type = FieldType::PLAYER2;
        } else {
            type = FieldType::PLAYER2_KING;
        }
    }

    return icons[type];
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

    return true;
}

enum MoveType {
    ILLEGAL,
    SHORT,
    LONG
};

bool Checkerboard::IsLegalMove(const Position from, const Position to)
{
    auto destinationState = GetFieldState(to);
    if (abs(from.indexI - to.indexI) == 1 && abs(from.indexJ - to.indexJ) == 1) {
        return destinationState.player == Player::NONE;
    } else if (abs(from.indexI - to.indexI) == 2 && abs(from.indexJ - to.indexJ) == 2) {
        auto i = to.indexI + (from.indexI - to.indexI);
        auto j = to.indexJ + (from.indexJ - to.indexJ);
        auto interState = Checkerboard::state[i][j];

        return interState.player != Player::NONE;
    }

    return false;
}

MoveType GetMoveType(const Position from, const Position to)
{
    return MoveType::ILLEGAL;
}

Piece Checkerboard::GetFieldState(const Position position)
{
    return Checkerboard::state[position.indexI][position.indexJ];
}

void Checkerboard::MovePiece(const Position from, const Position to)
{
    auto fieldStart = Checkerboard::state[from.indexI][from.indexJ];
    Checkerboard::state[to.indexI][to.indexJ] = fieldStart;
    Checkerboard::state[from.indexI][from.indexJ].player = Player::NONE;
    Checkerboard::state[from.indexI][from.indexJ].type = PieceType::EMPTY;
}