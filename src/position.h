#ifndef POSITION_H
#define POSITION_H

#include "constants.h"
#include <optional>
#include <set>

class Position
{
public:
    char letter;
    int number;
    int y;
    int x;

    Position(char letter, int number);
    Position(int x, int y);
    static std::optional<Position> Construct(const std::string position);
    bool operator==(const Position& other);

private:
    static const std::set<char> availableLetters;
    static const int maxNumber = constants::BOARD_HEIGHT;

    static bool Validate(char letter, int number);
};

#endif