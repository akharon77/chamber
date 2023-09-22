#include "button.hpp"

static const FontCollection FONTS;

void Interactive::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        checkIn(event.mouseButton.x, event.mouseButton.y))
    {
        onPressed();
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
             event.mouseButton.button == sf::Mouse::Left  &&
             checkIn(event.mouseButton.x, event.mouseButton.y))
    {
        onReleased();
    }
    else if (event.type == sf::Event::MouseMoved &&
             checkIn(event.mouseMove.x, event.mouseMove.y))
    {
        onFocused();
    }
}

RectangleButton::RectangleButton(int32_t x = 0, int32_t y = 0, int32_t width = 0, int32_t height = 0, sf::Color btn_fill_color = sf::Color::White, sf::Color btn_outline_color = sf::Color::Black, const char *text = "", sf::Color text_color = sf::Color::Black) :
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height),
    m_rect({width, height})
{
    m_rect.setPosition(x, y);

    m_text.setString(text);
    m_text.setColor(text_color);
    m_text.setFont(m_base_font.getFont());

    // TODO
    m_text.setCharacterSize(15);
    m_text.setPosition(x, y);

    m_rect.setFillColor(btn_fill_color);
    m_rect.setOutlineColor(btn_outline_color);
}

void Button::draw(const sf::RenderWindow &window) const
{
    window.draw(m_rect);
    window.draw(m_text);
}

void ButtonManager::add(const Button &btn)
{
    m_btn_arr.push_back(&btn);
}

void ButtonManager::handleEvent(const sf::Event &event)
{
    for (size_t i = 0; i < m_btn_arr.size(); ++i)
        m_btn_arr.handleEvent(event);
}

