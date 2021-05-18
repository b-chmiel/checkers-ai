#ifndef POSITION_H
#define POSITION_H

#include "constants.h"
#include <optional>
#include <set>

class Position
{
public:
    char m_Letter;
    int m_Number;
    int m_Y;
    int m_X;

    Position(char letter, int number);
    Position(int x, int y);
    static std::optional<Position> Construct(const std::string position);
    bool operator==(const Position& other);

private:
    static const std::set<char> m_AvailableLetters;
    static const int maxNumber = constants::BOARD_HEIGHT;

    static bool Validate(char letter, int number);
};

#endif