#include "piece.h"
#include "player.h"
#include <string>

using namespace piece;

const std::string Piece::icons[5] = { "   ", " ⛀ ", " ⛂ ", " ⛁ ", " ⛃ " };

Piece::Piece()
    : player(player::NONE)
    , type(PieceType::EMPTY)
{
}

Piece::Piece(const player::PlayerType& player, const PieceType& type)
    : player(player)
    , type(type)
{
}

std::string Piece::GetIcon()
{
    FieldType type;

    if (Piece::player == player::PlayerType::NONE)
    {
        type = FieldType::NONE;
    }
    else if (Piece::player == player::PlayerType::PLAYER1)
    {
        type = (Piece::type == PieceType::MAN) ? FieldType::PLAYER1 : FieldType::PLAYER1_KING;
    }
    else
    {
        type = (Piece::type == PieceType::MAN) ? FieldType::PLAYER2 : FieldType::PLAYER2_KING;
    }

    return icons[type];
}