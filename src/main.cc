#include "availableMoves.h"
#include "board.h"
#include "player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<Point> ParsePath(std::string input)
{
    std::istringstream stream(input);
    std::string token;
    std::vector<Point> result;

    while (getline(stream, token, ' '))
    {
        auto position = Position::Construct(token);
        if (!position)
        {
            printf("Unrecognised position: %s\n", token.c_str());
            break;
        }

        Point point = { position->m_X, position->m_Y };
        result.push_back(point);
    }

    return result;
}

int main()
{
    auto board = board::Checkerboard();

    std::string moveHistory;
    std::string input;
    std::vector<std::vector<Point>> availableMoves;

    do
    {
        board.Show();

        printf("\n%s>>> ", player::Player::GetPlayerName(board.m_CurrentPlayer).c_str());

        getline(std::cin, input);
        moveHistory += "\n" + input;
        if (input == "exit")
        {
            printf("Move history: \n %s", moveHistory.c_str());
            return 0;
        }

        auto path = ParsePath(input);

        availableMoves = AvailableMoves::GetAvailableMoves(board, board.m_CurrentPlayer);
        bool isMoveCorrect = false;
        for (const auto& move : availableMoves)
        {
            if (move == path)
            {
                board.Move(path);
                isMoveCorrect = true;
                break;
            }
        }

        if (!isMoveCorrect)
        {
            printf("%s\n", "Cannot make a move");
        }
    } while (!board.IsGameCompleted() && availableMoves.size() != 0);

    board.Show();
    auto playerLost = player::Player::GetAnotherPlayer(board.m_CurrentPlayer);
    printf("\nWon player: %s", player::Player::GetPlayerName(playerLost).c_str());

    printf("Move history: \n %s", moveHistory.c_str());
    return 0;
}
