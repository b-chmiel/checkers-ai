#include "board.h"
#include "player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto ParsePath(std::string input)
{
    std::istringstream stream(input);
    std::string token;
    std::vector<Position> result;

    while (getline(stream, token, ' ')) {
        auto position = Position::Construct(token);
        if (!position) {
            printf("Unrecognised position: %s\n", token.c_str());
            break;
        }

        result.push_back(*position);
    }

    return result;
}

int main()
{
    auto board = board::Checkerboard();
    board.Show();

    std::string input;
    while (!board.IsGameCompleted()) {
        printf("\n%s>>> ", player::Player::GetPlayerName(board.currentPlayer).c_str());
        getline(std::cin, input);
        if (input == "exit") {
            return 0;
        }

        auto path = ParsePath(input);

        if (path.size() < 2 || !board.Move(path)) {
            printf("%s\n", "Cannot make a move");
        }

        board.Show();
    }

    auto playerLost = player::Player::GetAnotherPlayer(board.currentPlayer);
    printf("\nWon player: %s", player::Player::GetPlayerName(playerLost).c_str());

    return 0;
}
