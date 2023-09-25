#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "molecule.hpp"

const uint32_t SCREEN_WIDTH  = 640; 
const uint32_t SCREEN_HEIGHT = 480;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "chamber");

    Chamber chamber({50, 35}, 300, 400);

    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {0.3, 0.2}));
    chamber.addMolecule(new CircleMolecule(1, {10, 100}, {-0.5, 0.1}));
    chamber.addMolecule(new SquareMolecule(1, {100, 10}, {0.1, 0.3}));
    chamber.addMolecule(new SquareMolecule(1, {100, 100}, {-0.4, -0.2}));
    chamber.addMolecule(new SquareMolecule(1, {150, 150}, {-0.8, -0.2}));
    chamber.addMolecule(new SquareMolecule(1, {140, 100}, {-0.4, -0.2}));

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
