#include "position.h"
#include "constants.h"
#include <string>

std::set<char> Position::availableLetters { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

Position::Position(char letter, int number)
    : letter(letter)
    , number(number)
{
    Position::y = constants::BOARD_HEIGHT - number;
    Position::x = letter - 'A';
}

std::experimental::optional<Position> Position::Construct(const std::string position)
{
    if (position.length() != 2) {
        return std::experimental::nullopt;
    }

    char letter = position.at(0);
    int number = position.at(1) - '0';

    if (Position::Validate(letter, number)) {
        return Position(letter, number);
    }

    return std::experimental::nullopt;
}

bool Position::Validate(char letter, int number)
{
    if (availableLetters.find(letter) == availableLetters.end()) {
        return false;
    }
    if (number > Position::maxNumber || number < 1) {
        return false;
    }

    return true;
}

bool Position::operator==(const Position& other)
{
    return other.y == Position::y && other.x == Position::x;
}