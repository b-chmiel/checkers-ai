#include "game.h"
#include "../../Board/board.h"
#include "../../Board/constants.h"
#include "../../MoveInput/Random/randomMove.h"
#include "../../Utils/player.h"
#include "gameStats.h"
#include "timer.h"
#include <optional>

using namespace game;

Game::Game(const GameParams& params)
    : m_Params(params)
{
}

game_stats::GameStats Game::PlayGame() const
{
    game_stats::GameStats stats;
    auto board = board::Checkerboard();

#ifdef GUI
    board.Show();
#endif

    auto timeGame = timer::Timer();
    auto timePlayer1 = timer::Timer();
    auto timePlayer2 = timer::Timer();

    int moveCount = 1;

    timeGame.Begin();
    while (true)
    {
        if (moveCount >= constants::DRAW_THRESHOLD)
        {
            stats.Winner = board.GetWinner();
            break;
        }

        timePlayer1.Begin();
        if (!PlayMove(m_Params.player1Ai, board, moveCount))
        {
            stats.Winner = player::PlayerType::PLAYER2;
            break;
        }
        timePlayer1.End();

        stats.AppendMove(timePlayer1.TimeDifferenceInSeconds());
        moveCount++;

        timePlayer2.Begin();
        if (!PlayMove(m_Params.player2Ai, board, moveCount))
        {
            stats.Winner = player::PlayerType::PLAYER1;
            break;
        }
        timePlayer2.End();

        stats.AppendMove(timePlayer2.TimeDifferenceInSeconds());
        moveCount++;
    }
    timeGame.End();

    stats.GameDuration = timeGame.TimeDifferenceInSeconds();
    return stats;
}

bool Game::PlayMove(std::shared_ptr<MoveInput> method, board::Checkerboard& board, int moveCount) const
{
    std::optional<Move> move;

    if (m_Params.params.RandomMoves * 2 > moveCount)
    {
        auto rndMove = RandomMove();
        move = rndMove.ProcessMove(board, moveCount);
    }
    else
    {
        move = method->ProcessMove(board, moveCount);
    }

    if (!move)
    {
        return false;
    }

    board.MovePiece(*move);

#ifdef GUI
    board.Show();
#endif

    return true;
}