#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Window/Event.hpp>

class Widget
{
public:
    virtual void handleEvent(const sf::Event &event) = 0;
    virtual void draw(sf::RenderWindow &window)      = 0;
};

#endif  // WIDGET_HPP

