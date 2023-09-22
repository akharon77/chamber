#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "molecule.hpp"

const uint32_t SCREEN_WIDTH  = 640; 
const uint32_t SCREEN_HEIGHT = 480;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "chamber");

    Chamber chamber({50, 35}, 300, 400);

    new CircleMolecule(&chamber, 1, {25, 25}, {0.1, 0.1});
    // CircleMolecule mol2(&chamber, 1, {5, 10}, {0.2, 0.1});

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        chamber.update();
        chamber.draw(window);

        window.display();
    }

    return 0;
}
