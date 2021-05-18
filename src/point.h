#ifndef POINT_H
#define POINT_H

class Point
{
public:
    int x;
    int y;
    bool operator==(const Point& other) const;
};

#endif