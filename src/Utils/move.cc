#include "move.h"
#include "point.h"
#include <vector>

Move::Move(const Point& point)
{
    Path = std::vector<Point> { point };
}

Move::Move(const std::vector<Point>& path)
    : Path(path)
{
}

bool Move::operator==(const Move& other) const
{
    return Path == other.Path;
}