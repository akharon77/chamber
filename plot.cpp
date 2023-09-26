#include "plot.hpp"

const int32_t PLOT_OUTLINE_THICKNESS = 2;

Plot::Plot(Vector2f pos, float width, float height, int32_t size, float max_val) :
    m_pos     (pos),
    m_width   (width),
    m_height  (height),
    m_size    (size),
    m_start   (0),
    m_max_val (max_val),
    m_buf     (new float[m_size]),
    m_points  (new sf::Vertex[m_size]),
    m_rect    ({width, height})
{
    for (int32_t i = 0; i < m_size; ++i)
    {
        m_buf[i] = 0;
        m_points[i].position = {0, 0};
    }
    m_rect.setPosition(m_pos);
    m_rect.setOutlineThickness(PLOT_OUTLINE_THICKNESS);
    m_rect.setFillColor(sf::Color::Black);
}

void Plot::emit(float val)
{
    m_buf[m_start++] = val;
    if (m_start >= m_size)
        m_start -= m_size;

    recalcPoints();
}

void Plot::recalcPoints()
{
    float max_val = m_max_val;

    for (int32_t i = 0; i < m_size; ++i)
        if (m_buf[i] > max_val)
            max_val = m_buf[i];

    for (int32_t i = 0, j = m_start; i < m_size; ++i, ++j)
    {
        if (j >= m_size)
            j -= m_size;

        m_points[j].position = m_pos + Vector2f{m_width / (m_size - 1) * i, m_height * (1 - 0.75 * m_buf[j] / max_val)};
    }
}

void Plot::draw(sf::RenderWindow &window)
{
    window.draw(m_rect);
    window.draw(m_points + m_start, m_size - m_start, sf::LinesStrip);

    // sf::Vertex line[] = 
    // {
    //     m_points[(m_size + m_start - 1) % m_size],
    //     m_points[m_start]
    // };
    // window.draw(line, 2, sf::Lines);

    window.draw(m_points, m_start, sf::LinesStrip);
}

