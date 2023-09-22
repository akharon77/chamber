#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

using Vector2f = sf::Vector2f;

const double EPS = 1e-6;

double dot  (const Vector2f &lhs, const Vector2f &rhs);
double len2 (const Vector2f &rhs);
double len  (const Vector2f &rhs);

#endif  // VECTOR2F_HPP

