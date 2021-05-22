#include "Board/board.h"
#include "MoveInput/MinMax/EvaluationFunction/evaluateOne.h"
#include "MoveInput/MinMax/EvaluationFunction/evaluationFunction.h"
#include "MoveInput/MinMax/alphaBeta.h"
#include "MoveInput/MinMax/minMax.h"
#include "MoveInput/User/userInput.h"
#include "MoveInput/availableMoves.h"
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
    alpha_beta::AlphaBeta alphaBeta(6);
    minmax::MinMax minMax(5);
    board.Show();

    int move = 1;
    while (true)
    {
        if (move >= 50)
        {
            std::cout << "DRAW" << std::endl;
            return 0;
        }

        auto availableMoves = AvailableMoves::GetAvailableMoves(board, board.CurrentPlayer.Type);
        std::cout << "\nAlphaBeta Evaluation: " << eval.Evaluate(board, availableMoves) << std::endl;
        std::cout << "MOVE: " << move++ << std::endl;

        auto v1 = alphaBeta.ProcessMove(board);

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

        availableMoves = AvailableMoves::GetAvailableMoves(board, board.CurrentPlayer.Type);
        std::cout << "\nMinMax Evaluation: " << eval.Evaluate(board, availableMoves) << std::endl;
        std::cout << "MOVE: " << move++ << std::endl;

        auto v2 = minMax.ProcessMove(board);

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
