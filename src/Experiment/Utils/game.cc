#include "game.h"
#include "../../Board/board.h"
#include "../../Utils/player.h"
#include "gameStats.h"
#include "timer.h"

using namespace game;

Game::Game(const GameParams& params)
    : m_Params(params)
{
}

game_stats::GameStats Game::PlayGame() const
{
    game_stats::GameStats stats;
    auto board = board::Checkerboard();
    // board.Show();

    auto timeGame = timer::Timer();
    auto timePlayer1 = timer::Timer();
    auto timePlayer2 = timer::Timer();

    int move = 1;

    timeGame.Begin();
    while (true)
    {
        if (move >= m_DrawThreshold)
        {
            stats.Winner = player::PlayerType::NONE;
            break;
        }

        timePlayer1.Begin();
        if (!PlayMove(m_Params.player1Ai, board))
        {
            stats.Winner = player::PlayerType::PLAYER2;
            break;
        }
        timePlayer1.End();

        stats.AppendMove(timePlayer1.TimeDifferenceInSeconds());
        move++;

        timePlayer2.Begin();
        if (!PlayMove(m_Params.player2Ai, board))
        {
            stats.Winner = player::PlayerType::PLAYER2;
            break;
        }
        timePlayer2.End();

        stats.AppendMove(timePlayer2.TimeDifferenceInSeconds());
        move++;
    }
    timeGame.End();

    stats.GameDuration = timeGame.TimeDifferenceInSeconds();
    return stats;
}

bool Game::PlayMove(std::shared_ptr<MoveInput> method, board::Checkerboard& board) const
{
    auto move = method->ProcessMove(board);

    if (!move)
    {
        return false;
    }

    board.MovePiece(*move);
    // board.Show();

    return true;
}