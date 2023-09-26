#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>

#include <cassert>

#include "widget.hpp"
#include "list.hpp"

using Vector2u = sf::Vector2u;

class Button : public Widget
{
protected:
    Vector2u m_pos;

    int32_t m_width;
    int32_t m_height;

    sf::Sprite m_sprite;
    sf::Texture m_texture;

    Vector2u m_default_pos;
    Vector2u m_pressed_pos;
    Vector2u m_focused_pos;

    bool checkIn(const Vector2u &pnt) const;

public:

    Button(Vector2u pos, int32_t width, int32_t height, sf::Texture texture, Vector2u default_pos, Vector2u pressed_pos, Vector2u focused_pos);

    virtual void handleEvent(const sf::Event &event)  override;
    virtual void draw(sf::RenderWindow &window) override;

    virtual void onPressed()  = 0;
    virtual void onReleased() = 0;
    virtual void onFocused()  = 0;

    Button(const Button &rhs) = delete;
    Button& operator = (const Button &rhs) = delete;

    ~Button() = default;
};

class Panel : public Widget
{
    BufferList<Widget*> m_buf_wdgs;
    List<Widget*>       m_wdgs;

public:
    
    Panel();
    ~Panel() = default;

    Panel(const Panel& rhs) = delete;
    Panel& operator = (const Panel& rhs) = delete;

    void add(Widget *wdg);

    void handleEvent(const sf::Event &event) override;
    void draw(sf::RenderWindow &window)      override;
};

#endif  // BUTTON_HPP

