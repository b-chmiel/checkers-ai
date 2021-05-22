#ifndef GAME_H
#define GAME_H

#include "../../MoveInput/MinMax/EvaluationFunction/evaluationFunction.h"
#include "../../MoveInput/moveInput.h"
#include "../../Utils/player.h"
#include "../experiment.h"
#include "gameStats.h"
#include <memory>

namespace game
{

struct GameParams
{
    std::shared_ptr<MoveInput> player1Ai;
    std::shared_ptr<MoveInput> player2Ai;
    experiment::Params params;
};

class Game
{
public:
    Game(const GameParams&);
    game_stats::GameStats PlayGame() const;

private:
    GameParams m_Params;

    bool PlayMove(std::shared_ptr<MoveInput> method, board::Checkerboard& board, int moveCount) const;
};
}
#endif