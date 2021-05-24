#include "gameStats.h"
#include <iomanip>
#include <iostream>
#include <vector>

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

    Player1WinRate = ((double)m_Player1Wins) / ((double)m_GameCount);
}

void TotalGameStats::Show() const
{
    int width = 20;
    std::cout << m_Depth
              << std::setw(width)
              << AvgMoveDuration
              << std::setw(width)
              << GameDuration
              << std::setw(width)
              << Player1WinRate
              << std::setw(width)
              << m_Player1Wins << "/"
              << m_GameCount
              << std::endl;
}

void TotalGameStats::ShowMany(const std::vector<TotalGameStats>& stats)
{
    int width = 20;

    std::cout << std::endl
              << "d"
              << std::setw(width)
              << "AvgMoveDuration[s]"
              << std::setw(width)
              << "GameDuration[s]"
              << std::setw(width)
              << "Player1WinRate" << std::endl;

    for (const auto& stat : stats)
    {
        stat.Show();
    }
}