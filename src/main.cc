#include "DrawBoard/board.h"
#include "GetMove/MinMax/EvaluationFunction/evaluateOne.h"
#include "GetMove/MinMax/EvaluationFunction/evaluationFunction.h"
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
    std::vector<Move> availableMoves;
    EvaluateOne eval;

    do
    {
        board.Show();
        availableMoves = AvailableMoves::GetAvailableMoves(board, board.CurrentPlayer.Type);
        std::cout << "\nEvaluation: " << eval.Evaluate(board) << std::endl;

        auto move = UserInput::GetMove(board, availableMoves);

        if (!move)
        {
            return 0;
        }

        board.MovePiece(*move);
    } while (!board.IsGameCompleted() && availableMoves.size() != 0);

    board.Show();
    auto playerLost = player::Player(board.CurrentPlayer.GetAnotherPlayer());
    printf("\nWon player: %s", playerLost.GetPlayerName().c_str());

    return 0;
}
