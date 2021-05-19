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
    PlayerType Type;
    Player();
    Player(PlayerType);

    std::string GetPlayerName() const;
    PlayerType GetAnotherPlayer() const;
    int MaxY() const;
    bool operator==(const Player&) const;
    bool operator!=(const Player&) const;

private:
    static std::map<player::PlayerType, std::string> m_PlayerNames;
};
}

#endif