#include "DrawBoard/board.h"
#include "GetMove/MinMax/EvaluationFunction/evaluateOne.h"
#include "GetMove/MinMax/EvaluationFunction/evaluationFunction.h"
#include "GetMove/MinMax/alphaBeta.h"
#include "GetMove/MinMax/minMax.h"
#include "GetMove/User/userInput.h"
#include "Utils/move.h"
#include "Utils/player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    auto board = board::Checkerboard();
    EvaluateOne eval;
    alpha_beta::AlphaBeta alphaBeta(50);
    minmax::MinMax minMax(3);
    board.Show();

    int i = 1;
    while (true)
    {
        std::cout << "\nAlphaBeta Evaluation: " << eval.Evaluate(board) << std::endl;
        std::cout << "MOVE: " << i++ << std::endl;

        auto v1 = alphaBeta.GetMove(board);

        if (!v1)
        {
            break;
        }

        board.MovePiece(*v1);

        board.Show();
        if (board.IsGameCompleted())
        {
            break;
        }

        std::cout << "\nMinmax Evaluation: " << eval.Evaluate(board) << std::endl;
        std::cout << "MOVE: " << i++ << std::endl;

        auto v2 = minMax.GetMove(board);

        if (!v2)
        {
            break;
        }
        board.MovePiece(*v2);

        board.Show();
        if (board.IsGameCompleted())
        {
            break;
        }
    }

    auto playerLost = player::Player(board.CurrentPlayer.GetAnotherPlayer());
    printf("\nWon player: %s", playerLost.GetPlayerName().c_str());

    return 0;
}
