/**
 * Math Vector 2D
 * 
 * Simple 2D Point
 */

#ifndef MATH_VECTOR_2D_H
#define MATH_VECTOR_2D_H

#include "../points/point2d.h"

struct MathVec2d
{
    Point2d start, end;

    MathVec2d() {}

    MathVec2d(const Point2d &start, const Point2d &end)
    {
        this->start = start;
        this->end = end;
    }

    MathVec2d &operator=(const MathVec2d &a)
    {
        start = {a.start.x, a.start.y};
        end = {a.end.x, a.end.y};
        return *this;
    }
};

MathVec2d operator*(float s, MathVec2d a)
{
    return MathVec2d(s * a.start, s * a.end);
}

#endif /* POINT_2D_H */