#include "player.h"
#include <string>

using namespace player;

std::map<PlayerType, std::string> Player::m_PlayerNames = { { player::PLAYER1, "PLAYER1" }, { player::PLAYER2, "PLAYER2" } };

std::string Player::GetPlayerName(PlayerType player)
{
    return Player::m_PlayerNames[player];
}

player::PlayerType Player::GetAnotherPlayer(PlayerType other)
{
    switch (other)
    {
    case PlayerType::PLAYER1:
        return PlayerType::PLAYER2;
    case PlayerType::PLAYER2:
        return PlayerType::PLAYER1;
    default:
        return PlayerType::NONE;
    }
}