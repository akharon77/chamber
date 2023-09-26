#include "button.hpp"

Button::Button(Vector2f pos, int32_t width, int32_t height, sf::Texture texture, Vector2u default_pos, Vector2u pressed_pos, Vector2u focused_pos) :
    m_pos(pos),
    m_width(width),
    m_height(height),
    m_texture(texture),
    m_default_pos(default_pos),
    m_pressed_pos(pressed_pos),
    m_focused_pos(focused_pos)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(m_default_pos.x, m_default_pos.y, m_width, m_height));
    m_sprite.setPosition({m_pos.x, m_pos.y});
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}

bool Button::checkIn(const Vector2f &pnt) const
{
    return m_pos.x <= pnt.x && pnt.x <= m_pos.x + m_width &&
           m_pos.y <= pnt.y && pnt.y <= m_pos.y + m_height;
}

void Button::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        checkIn({event.mouseButton.x, event.mouseButton.y}))
    {
        m_sprite.setTextureRect(sf::IntRect(m_pressed_pos.x, m_pressed_pos.y, m_width, m_height));
        onPressed();
    }
    else if (event.type == sf::Event::MouseButtonReleased &&
             event.mouseButton.button == sf::Mouse::Left  &&
             checkIn({event.mouseButton.x, event.mouseButton.y}))
    {
        m_sprite.setTextureRect(sf::IntRect(m_default_pos.x, m_default_pos.y, m_width, m_height));
        onReleased();
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        if (checkIn({event.mouseMove.x, event.mouseMove.y}))
        {
            m_sprite.setTextureRect(sf::IntRect(m_focused_pos.x, m_focused_pos.y, m_width, m_height));
            onFocused();
        }
        else
        {
            m_sprite.setTextureRect(sf::IntRect(m_default_pos.x, m_default_pos.y, m_width, m_height));
        }
    }
}

Panel::Panel() :
    m_buf_wdgs(1),
    m_wdgs(&m_buf_wdgs)
{}

void Panel::draw(sf::RenderWindow &window)
{
    int32_t anch = m_wdgs.GetHead();
    Node<Widget*> node = *m_wdgs.Get(anch);

    int32_t size = m_wdgs.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(window);
        anch = node.next;
        node = *m_wdgs.Get(anch);
    }
}

void Panel::handleEvent(const sf::Event &event)
{
    int32_t anch = m_wdgs.GetHead();
    Node<Widget*> node = *m_wdgs.Get(anch);

    int32_t size = m_wdgs.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->handleEvent(event);
        anch = node.next;
        node = *m_wdgs.Get(anch);
    }
}

void Panel::add(Widget *wdg)
{
    m_wdgs.PushBack(wdg);
}

