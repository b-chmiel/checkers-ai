#include "position.h"
#include "../../Board/constants.h"
#include <optional>
#include <string>

const std::set<char> Position::m_AvailableLetters { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

Position::Position(char letter, int number)
    : m_Letter(letter)
    , m_Number(number)
{
    Position::Y = constants::BOARD_HEIGHT - number;
    Position::X = letter - 'A';
}

Position::Position(int x, int y)
    : X(x)
    , Y(y)
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
    if (number > Position::m_MaxNumber || number < 1)
    {
        return false;
    }

    return true;
}

bool Position::operator==(const Position& other)
{
    return other.Y == Position::Y && other.X == Position::X;
}