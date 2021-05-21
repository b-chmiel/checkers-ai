#include "DrawBoard/board.h"
#include "GetMove/MinMax/EvaluationFunction/evaluateOne.h"
#include "GetMove/MinMax/EvaluationFunction/evaluationFunction.h"
#include "GetMove/MinMax/alphaBeta.h"
#include "GetMove/MinMax/minMax.h"
#include "GetMove/User/userInput.h"
#include "GetMove/availableMoves.h"
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
    alpha_beta::AlphaBeta alphaBeta(8);
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
        std::cout << "\nAlphaBeta2 Evaluation: " << eval.Evaluate(board, availableMoves) << std::endl;
        std::cout << "MOVE: " << move++ << std::endl;

        auto v2 = alphaBeta.ProcessMove(board);

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
