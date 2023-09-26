#ifndef PLOT_HPP
#define PLOT_HPP

#include <SFML/Graphics.hpp>

#include "vector2f.hpp"

class Plot
{
    Vector2f m_pos;
    float    m_width;
    float    m_height;

    int32_t     m_size;
    int32_t     m_start;
    float       m_max_val;
    float      *m_buf;
    sf::Vertex *m_points;

    sf::RectangleShape m_rect;

    void recalcPoints();

public:
    Plot(Vector2f pos, float width, float height, int32_t size, float max_val);

    void emit(float val);

    void draw(sf::RenderWindow &window);

    Plot(const Plot &rhs) = delete;
    Plot& operator = (const Plot &rhs) = delete;
    ~Plot() = default;
};

#endif  // PLOT_HPP
