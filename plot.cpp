#include "plot.hpp"

Plot::Plot(Vector2f pos, float width, float height, int32_t size) :
    m_pos    (pos),
    m_width  (width),
    m_height (height),
    m_size   (size),
    m_start  (0),
    m_buf    (new float[m_size]),
    m_points (new sf::Vertex[m_size])
{
    for (int32_t i = 0; i < m_size; ++i)
    {
        m_buf[i] = 0;
        m_points[i].pos = {0, 0};
    }
}

void Plot::emit(float val)
{
    m_buf[m_start++] = val;
    recalcPoints();
}

void Plot::recalcPoints()
{
    float max_val = 0;
    for (int32_t i = 0; i < m_size; ++i)
        if (m_buf[i] > max_val)
            max_val = m_buf[i];

    for (int32_t i = 0; i < m_size; ++i)
        m_points[i].position = m_pos + Vector2f{m_width / (m_size - 1) * ind, m_height * (1 - val / m_max)};
}

