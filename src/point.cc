#include "point.h"

bool Point::operator==(const Point& other) const
{
    return other.y == Point::y && other.x == Point::x;
}
