#include "gameStats.h"
#include <iostream>

using namespace game_stats;

void GameStats::AppendMove(double time)
{
    AvgMoveDuration = (AvgMoveDuration + time) / 2.0;
}

TotalGameStats::TotalGameStats(int depth)
    : AvgMoveDuration(0)
    , GameDuration(0)
    , Player1WinRate(0)
    , m_GameCount(0)
    , m_Player1Wins(0)
    , m_Depth(depth)
{
}

void TotalGameStats::AppendGame(const GameStats& stats)
{
    AvgMoveDuration = (AvgMoveDuration + stats.AvgMoveDuration) / 2.0;
    GameDuration = (GameDuration + stats.GameDuration) / 2.0;

    m_GameCount++;
    if (stats.Winner == player::PlayerType::PLAYER1)
    {
        m_Player1Wins++;
    }

    Player1WinRate = (double)m_Player1Wins / (double)m_GameCount;
}

void TotalGameStats::Show() const
{
    std::cout << std::endl
              << "d\t"
              << "AvgMoveDuration\t"
              << "GameDuration\t"
              << "[s]" << std::endl;

    std::cout << m_Depth << "\t" << AvgMoveDuration << "\t" << GameDuration << "\t" << Player1WinRate << std::endl;
}