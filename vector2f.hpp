#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

using Vector2f = sf::Vector2f;
using Vector2u = sf::Vector2u;

const float EPS = 1e-6;

float dot  (const Vector2f &lhs, const Vector2f &rhs);
float len2 (const Vector2f &rhs);
float len  (const Vector2f &rhs);

#endif  // VECTOR2F_HPP

