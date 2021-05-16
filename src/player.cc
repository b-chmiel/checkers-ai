#include "player.h"
#include <string>

std::string player::GetPlayerName(PlayerType player)
{
    switch (player) {
    case PlayerType::PLAYER1:
        return "PLAYER1";
    case PlayerType::PLAYER2:
        return "PLAYER2";
    default:
        return "NONE";
    }
}

player::PlayerType player::GetAnotherPlayer(PlayerType other)
{
    switch (other) {
    case PlayerType::PLAYER1:
        return PlayerType::PLAYER2;
    case PlayerType::PLAYER2:
        return PlayerType::PLAYER1;
    default:
        return PlayerType::NONE;
    }
}