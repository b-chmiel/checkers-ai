#include "availableMoves.h"
#include "board.h"
#include "player.h"
#include "userInput.h"
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
        availableMoves = AvailableMoves::GetAvailableMoves(board, board.m_CurrentPlayer);

        auto move = UserInput::GetUserInput(board, availableMoves);
        if (!move)
        {
            return 0;
        }

        board.Move(*move);

    } while (!board.IsGameCompleted() && availableMoves.size() != 0);

    board.Show();
    auto playerLost = player::Player::GetAnotherPlayer(board.m_CurrentPlayer);
    printf("\nWon player: %s", player::Player::GetPlayerName(playerLost).c_str());

    return 0;
}
