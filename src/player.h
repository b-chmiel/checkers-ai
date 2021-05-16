#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace player {
enum PlayerType {
    NONE,
    PLAYER1,
    PLAYER2
};

std::string GetPlayerName(PlayerType type);
PlayerType GetAnotherPlayer(PlayerType type);
}

#endif