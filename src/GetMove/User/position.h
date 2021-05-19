#ifndef POSITION_H
#define POSITION_H

#include "../../DrawBoard/constants.h"
#include <optional>
#include <set>

class Position
{
public:
    int X;
    int Y;

    Position(char letter, int number);
    Position(int x, int y);
    static std::optional<Position> Construct(const std::string position);
    bool operator==(const Position& other);

private:
    char m_Letter;
    int m_Number;

    static const std::set<char> m_AvailableLetters;
    static const int m_MaxNumber = constants::BOARD_HEIGHT;

    static bool Validate(char letter, int number);
};

#endif