#ifndef POINT_H
#define POINT_H

class Point
{
public:
    int m_X;
    int m_Y;
    bool operator==(const Point& other) const;
};

#endif