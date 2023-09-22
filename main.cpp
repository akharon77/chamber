#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

const uint32_t SCREEN_WIDTH  = 1024; 
const uint32_t SCREEN_HEIGHT = 740;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "chamber");

    //

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear(sf::Color::White);

        //

        window.display();
    }

    return 0;
}
