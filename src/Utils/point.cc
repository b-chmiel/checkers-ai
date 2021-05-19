#include "point.h"

bool Point::operator==(const Point& other) const
{
    return other.Y == Point::Y && other.X == Point::X;
}
