#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cassert>
#include <vector>

extern static const FontCollection FONTS;

class FontCollection
{
    sf::Font m_font;

public:

    FontCollection()
    {
        assert(m_font.loadFromFile("arial.ttf"));
    }

    const sf::Font& getArialFont() const
    {
        return m_font;
    }
};

class Interactive
{
protected:

    virtual bool checkIn (int32_t x, int32_t y) const = 0;

    virtual void onPressed()  = 0;
    virtual void onReleased() = 0;
    virtual void onFocused()  = 0;

public:

    void handleEvent(const sf::Event &event);
};

class RectangleButton : public Interactive
{
    int32_t m_x;
    int32_t m_y;

    int32_t m_width;
    int32_t m_height;

    sf::RectangleShape m_rect;
    sf::Text           m_text;

protected:

    bool checkIn(int32_t x, int32_t y) const override
    {
        return m_x <= x && x <= m_x + m_width &&
               m_y <= y && y <= m_y + m_height;
    }

public:

    RectangleButton(int32_t x = 0, int32_t y = 0, int32_t width = 0, int32_t height = 0, sf::Color btn_fill_color = sf::Color::White, sf::Color btn_outline_color = sf::Color::Black, const char *text = "", sf::Color text_color = sf::Color::Black);

    void draw(const sf::RenderWindow &window) const;

    RectangleButton(const RectangleButton &rhs) = default;
    RectangleButton& operator = (const RectangleButton &rhs) = default;

    ~RectangleButton() = default;
};

class ButtonManager
{
    std::vector<Button*> m_btn_arr;

public:
    
    ButtonManager() = default;
    ~ButtonManager() = default;

    ButtonManager(const ButtonManager& rhs) = delete;
    ButtonManager& operator = (const ButtonManager& rhs) = delete;

    void add(const Button &btn);
    void handleEvent(const sf::Event &event);
};

#endif  // BUTTON_HPP

