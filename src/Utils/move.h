#ifndef MOVE_H
#define MOVE_H

#include "point.h"
#include <vector>

class Move
{
public:
    std::vector<Point> Path;
    Move() = default;
    Move(const Point& point);
    Move(const std::vector<Point>& path);
    bool operator==(const Move& other) const;
};

#endif