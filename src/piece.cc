#include "piece.h"
#include "player.h"
#include <string>

using namespace piece;

const std::string Piece::icons[5] = { "   ", " ⛀ ", " ⛂ ", " ⛁ ", " ⛃ " };

Piece::Piece()
    : m_Player(player::NONE)
    , m_Type(PieceType::EMPTY)
{
}

Piece::Piece(const player::PlayerType& player, const PieceType& type)
    : m_Player(player)
    , m_Type(type)
{
}

std::string Piece::GetIcon()
{
    FieldType type;

    if (Piece::m_Player == player::PlayerType::NONE)
    {
        type = FieldType::NONE;
    }
    else if (Piece::m_Player == player::PlayerType::PLAYER1)
    {
        type = (Piece::m_Type == PieceType::MAN) ? FieldType::PLAYER1 : FieldType::PLAYER1_KING;
    }
    else
    {
        type = (Piece::m_Type == PieceType::MAN) ? FieldType::PLAYER2 : FieldType::PLAYER2_KING;
    }

    return icons[type];
}