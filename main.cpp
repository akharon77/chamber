#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "molecule.hpp"

const uint32_t SCREEN_WIDTH  = 640; 
const uint32_t SCREEN_HEIGHT = 480;
const int32_t UPD_TIME_MS = 4;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "chamber");

    Chamber chamber({50, 35}, 300, 400);

    chamber.addMolecule(new CircleMolecule(1, {10, 10},   { 5.3,  4.2}));
    chamber.addMolecule(new CircleMolecule(1, {10, 100},  {-6.5,  5.1}));
    chamber.addMolecule(new SquareMolecule(1, {100, 10},  { 7.1,  5.3}));
    chamber.addMolecule(new SquareMolecule(1, {100, 100}, {-5.4, -6.2}));
    chamber.addMolecule(new SquareMolecule(1, {150, 150}, {-6.8, -5.2}));
    chamber.addMolecule(new SquareMolecule(1, {140, 100}, {-7.4, -7.2}));

    sf::Clock upd_clock;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (upd_clock.getElapsedTime().asMilliseconds() >= UPD_TIME_MS)
        {
            window.clear(sf::Color::Black);
            chamber.update();
            chamber.draw(window);
            upd_clock.restart();
        }

        window.display();
    }

    return 0;
}
