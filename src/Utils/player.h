#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <string>

namespace player
{
enum PlayerType
{
    NONE,
    PLAYER1,
    PLAYER2
};

class Player
{
public:
    static std::string GetPlayerName(PlayerType type);
    static PlayerType GetAnotherPlayer(PlayerType type);

private:
    static std::map<player::PlayerType, std::string> m_PlayerNames;
};
}

#endif