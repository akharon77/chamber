#include "vector2f.hpp"

float dot(const Vector2f &lhs, const Vector2f &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float len2(const Vector2f &rhs)
{
    return dot(rhs, rhs);
}

float len(const Vector2f &rhs)
{
    return sqrt(len2(rhs));
}
