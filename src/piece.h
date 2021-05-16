#ifndef PIECE_H
#define PIECE_H

#include "player.h"
#include <string>

namespace piece {
enum PieceType {
    EMPTY,
    MAN,
    KING
};
enum FieldType {
    NONE,
    PLAYER1,
    PLAYER2,
    PLAYER1_KING,
    PLAYER2_KING
};

class Piece {

public:
    player::PlayerType player;
    PieceType type;

    Piece() = default;
    Piece(const player::PlayerType player, const PieceType type);
    std::string GetIcon();

private:
    static std::string icons[5];
};
}

#endif