#include "piece.h"
#include "player.h"
#include <string>

using namespace piece;

std::string Piece::icons[5] = { "   ", " ⛀ ", " ⛂ ", " ⛁ ", " ⛃ " };

Piece::Piece(const player::PlayerType player, const PieceType type)
{
    Piece::player = player;
    Piece::type = type;
}

std::string Piece::GetIcon()
{
    FieldType type;

    if (Piece::player == player::PlayerType::NONE) {
        type = FieldType::NONE;
    } else if (Piece::player == player::PlayerType::PLAYER1) {
        if (Piece::type == PieceType::MAN) {
            type = FieldType::PLAYER1;
        } else {
            type = FieldType::PLAYER1_KING;
        }
    } else {
        if (Piece::type == PieceType::MAN) {
            type = FieldType::PLAYER2;
        } else {
            type = FieldType::PLAYER2_KING;
        }
    }

    return icons[type];
}