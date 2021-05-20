/**
 * Point 2D
 * 
 * Simple 2D Point
 */

#ifndef POINT_2D_H
#define POINT_2D_H

struct Point2d
{
    float x, y;
    Point2d() : x(0.0f), y(0.0f) {}
    Point2d(float x, float y) : x(x), y(y) {}

    Point2d &operator=(const Point2d &a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }
};

Point2d operator+(Point2d a, Point2d b)
{
    return Point2d(a.x + b.x, a.y + b.y);
}

Point2d operator-(Point2d a, Point2d b)
{
    return Point2d(a.x - b.x, a.y - b.y);
}

Point2d operator*(float s, Point2d a)
{
    return Point2d(s * a.x, s * a.y);
}

#endif /* POINT_2D_H */