#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "position.h"
#include <vector>
namespace board {

enum Player {
    NONE,
    PLAYER1,
    PLAYER2
};

enum PieceType {
    EMPTY,
    MAN,
    KING
};
class Piece {

public:
    Player player;
    PieceType type;

    Piece() = default;
    Piece(const Player player, const PieceType type);
};

class Checkerboard {
public:
    Piece state[constants::BOARD_HEIGHT][constants::BOARD_WIDTH];
    Checkerboard();
    void Show();
    bool Move(const std::vector<Position> path);
    bool IsGameCompleted();

private:
    Player currentPlayer = Player::PLAYER1;
    const char* GetFieldIcon(int i, int j);
    void PrintLettersBelow();
    Piece GetFieldState(const Position position);
    void MovePiece(const Position from, const Position to);
    bool IsLegalMove(const Position from, const Position to);
};
}

#endif