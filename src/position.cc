#include "position.h"
#include "constants.h"
#include <optional>
#include <string>

const std::set<char> Position::m_AvailableLetters { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

Position::Position(char letter, int number)
    : m_Letter(letter)
    , m_Number(number)
{
    Position::m_Y = constants::BOARD_HEIGHT - number;
    Position::m_X = letter - 'A';
}

Position::Position(int x, int y)
    : m_Y(y)
    , m_X(x)
{
    Position::m_Letter = 'A' + x;
    Position::m_Number = constants::BOARD_HEIGHT - y;
}

std::optional<Position> Position::Construct(const std::string position)
{
    if (position.length() != 2)
    {
        return std::nullopt;
    }

    char letter = position.at(0);
    int number = position.at(1) - '0';

    if (Position::Validate(letter, number))
    {
        return Position(letter, number);
    }

    return std::nullopt;
}

bool Position::Validate(char letter, int number)
{
    if (m_AvailableLetters.find(letter) == m_AvailableLetters.end())
    {
        return false;
    }
    if (number > Position::maxNumber || number < 1)
    {
        return false;
    }

    return true;
}

bool Position::operator==(const Position& other)
{
    return other.m_Y == Position::m_Y && other.m_X == Position::m_X;
}