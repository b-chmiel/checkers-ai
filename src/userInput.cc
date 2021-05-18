#include "userInput.h"
#include "board.h"
#include "player.h"
#include "point.h"
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

std::optional<std::vector<Point>> UserInput::GetUserInput(const board::Checkerboard& board, const std::vector<std::vector<Point>>& availableMoves)
{
    while (true)
    {
        std::string input;

        printf("\n%s>>> ", player::Player::GetPlayerName(board.CurrentPlayer).c_str());

        getline(std::cin, input);
        if (input == "exit")
        {
            return std::nullopt;
        }

        auto path = ParsePath(input);

        for (const auto& move : availableMoves)
        {
            if (move == path)
            {
                return path;
            }
        }

        printf("%s\n", "Cannot make a move");
    }
}

std::vector<Point> UserInput::ParsePath(std::string input)
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

        Point point = { position->X, position->Y };
        result.push_back(point);
    }

    return result;
}