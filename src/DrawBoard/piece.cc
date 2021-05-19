#include "piece.h"
#include "../Utils/player.h"
#include <string>

using namespace piece;

const std::string Piece::m_Icons[5] = { "   ", " ⛀ ", " ⛂ ", " ⛁ ", " ⛃ " };

Piece::Piece()
    : Player(player::NONE)
    , Type(PieceType::EMPTY)
{
}

Piece::Piece(const player::Player& player, const PieceType& type)
    : Player(player)
    , Type(type)
{
}

std::string Piece::GetIcon()
{
    FieldType type;

    if (Piece::Player.Type == player::PlayerType::NONE)
    {
        type = FieldType::NONE;
    }
    else if (Piece::Player.Type == player::PlayerType::PLAYER1)
    {
        type = (Piece::Type == PieceType::MAN) ? FieldType::PLAYER1 : FieldType::PLAYER1_KING;
    }
    else
    {
        type = (Piece::Type == PieceType::MAN) ? FieldType::PLAYER2 : FieldType::PLAYER2_KING;
    }

    return m_Icons[type];
}