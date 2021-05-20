/**
 * Point 3D
 * 
 * Simple 3D Point
 */

#ifndef POINT_3D_H
#define POINT_3D_H

struct Point3d
{
    float x, y, z;
    Point3d() : x(0.0f), y(0.0f), z(0.0f) {}
    Point3d(float x, float y, float z) : x(x), y(y), z(z) {}

    Point3d &operator=(const Point3d &a)
    {
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }
};

Point3d operator+(Point3d a, Point3d b)
{
    return Point3d(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point3d operator-(Point3d a, Point3d b)
{
    return Point3d(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point3d operator*(float s, Point3d a)
{
    return Point3d(s * a.x, s * a.y, s * a.z);
}

#endif /* POINT_3D_H */