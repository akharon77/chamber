#include "vector2f.hpp"

double dot(const Vector2f &lhs, const Vector2f &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double len2(const Vector2f &rhs)
{
    return dot(rhs, rhs);
}

double len(const Vector2f &rhs)
{
    return sqrt(len2(rhs));
}
