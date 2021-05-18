#ifndef POINT_H
#define POINT_H

class Point
{
public:
    int X;
    int Y;
    bool operator==(const Point& other) const;
};

#endif