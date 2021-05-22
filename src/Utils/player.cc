#include "player.h"
#include "../Board/constants.h"
#include <string>

using namespace player;

std::map<PlayerType, std::string> Player::m_PlayerNames = { { player::PLAYER1, "PLAYER1" }, { player::PLAYER2, "PLAYER2" } };

Player::Player()
    : Type(PlayerType::NONE)
{
}

Player::Player(PlayerType type)
    : Type(type)
{
}

std::string Player::GetPlayerName() const
{
    return Player::m_PlayerNames[Type];
}

PlayerType Player::GetAnotherPlayer() const
{
    switch (Type)
    {
    case PlayerType::PLAYER1:
        return PlayerType::PLAYER2;
    case PlayerType::PLAYER2:
        return PlayerType::PLAYER1;
    default:
        return PlayerType::NONE;
    }
}

int Player::MaxY() const
{
    switch (Type)
    {
    case PlayerType::PLAYER1:
        return 0;
    case PlayerType::PLAYER2:
        return constants::BOARD_HEIGHT - 1;
    default:
        throw "Max y unexpected player";
        return 0;
    }
}

bool Player::operator==(const Player& other) const
{
    return Type == other.Type;
}

bool Player::operator!=(const Player& other) const
{
    return !(*this == other);
}