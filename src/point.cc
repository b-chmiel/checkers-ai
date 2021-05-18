#include "point.h"

bool Point::operator==(const Point& other) const
{
    return other.m_Y == Point::m_Y && other.m_X == Point::m_X;
}
