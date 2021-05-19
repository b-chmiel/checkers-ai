#include "DrawBoard/board.h"
#include "GetMove/User/userInput.h"
#include "GetMove/availableMoves.h"
#include "Utils/player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    auto board = board::Checkerboard();
    std::vector<std::vector<Point>> availableMoves;
    do
    {
        board.Show();
        availableMoves = AvailableMoves::GetAvailableMoves(board, board.CurrentPlayer);

        auto move = UserInput::GetMove(board, availableMoves);
        if (!move)
        {
            return 0;
        }

        board.Move(*move);

    } while (!board.IsGameCompleted() && availableMoves.size() != 0);

    board.Show();
    auto playerLost = player::Player::GetAnotherPlayer(board.CurrentPlayer);
    printf("\nWon player: %s", player::Player::GetPlayerName(playerLost).c_str());

    return 0;
}
