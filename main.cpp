#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "molecule.hpp"
#include "chamber_btn_ctrl.hpp"
#include "plot.hpp"

const uint32_t SCREEN_WIDTH  = 770; 
const uint32_t SCREEN_HEIGHT = 620;
const uint32_t UPD_TIME_MS   = 5;
const uint32_t PLOT_TIME_MS  = 50;

const Vector2f CHAMBER_POS       = {50,  35};
const Vector2f CHAMBER_SIZE      = {300, 420};

const Vector2f PLOT_SIZE_WH      = {300, 100};
const Vector2f PRESSURE_PLOT_POS = {400, 35};
const Vector2f ENERGY_PLOT_POS   = {400, 260};
const int32_t  PLOT_SIZE_CNT     = 50;

const Vector2f BTN_TEMP_INC_POS  = {400, 400};
const Vector2f BTN_TEMP_DEC_POS  = {470, 400};
const float DELTA_TEMP = 5;

const Vector2f BTN_PIST_INC_POS  = {400, 170};
const Vector2f BTN_PIST_DEC_POS  = {470, 170};
const float DELTA_PIST = 5;

const Vector2f BTN_MOLS_CIRC_POS = {50, 480};
const Vector2f BTN_MOLS_SQR_POS  = {170, 480};
const int32_t DELTA_MOLS = 5;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "chamber");

    Chamber chamber(CHAMBER_POS, CHAMBER_SIZE.x, CHAMBER_SIZE.y);
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));
    chamber.addMolecule(new CircleMolecule(1, {10, 10}, {10, 10}));

    AssetsManager assets;
    ChamberTemperatureBtnCtrl btn_temp_inc(BTN_TEMP_INC_POS, &chamber,  DELTA_TEMP, &assets);
    ChamberTemperatureBtnCtrl btn_temp_dec(BTN_TEMP_DEC_POS, &chamber, -DELTA_TEMP, &assets);

    ChamberPistonBtnCtrl btn_pist_inc(BTN_PIST_INC_POS, &chamber,  DELTA_PIST, &assets);
    ChamberPistonBtnCtrl btn_pist_dec(BTN_PIST_DEC_POS, &chamber, -DELTA_PIST, &assets);

    ChamberMolsBtnCtrl btn_mols_circ(BTN_MOLS_CIRC_POS, &chamber, Molecule::MoleculeType::CIRCLE, DELTA_MOLS, &assets);
    ChamberMolsBtnCtrl btn_mols_sqr(BTN_MOLS_SQR_POS, &chamber, Molecule::MoleculeType::SQUARE, DELTA_MOLS, &assets);

    sf::Clock upd_clock;
    sf::Clock plot_clock;

    Plot pressure_plot(PRESSURE_PLOT_POS, PLOT_SIZE_WH.x, PLOT_SIZE_WH.y, PLOT_SIZE_CNT, 1);
    Plot energy_plot  (ENERGY_PLOT_POS,   PLOT_SIZE_WH.x, PLOT_SIZE_WH.y, PLOT_SIZE_CNT, 1);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            btn_temp_inc.handleEvent(event);
            btn_temp_dec.handleEvent(event);

            btn_pist_inc.handleEvent(event);
            btn_pist_dec.handleEvent(event);

            btn_mols_circ.handleEvent(event);
            btn_mols_sqr.handleEvent(event);
        }

        if (upd_clock.getElapsedTime().asMilliseconds() >= UPD_TIME_MS)
        {
            window.clear(sf::Color::Black);
            chamber.update();
            upd_clock.restart();
        }

        if (plot_clock.getElapsedTime().asMilliseconds() >= PLOT_TIME_MS)
        {
            pressure_plot.emit(chamber.getPressure());
            energy_plot.emit(chamber.getEnergy());
            plot_clock.restart();
        }

        btn_temp_inc.draw(window);
        btn_temp_dec.draw(window);

        btn_pist_inc.draw(window);
        btn_pist_dec.draw(window);

        btn_mols_circ.draw(window);
        btn_mols_sqr.draw(window);

        chamber.draw(window);

        pressure_plot.draw(window);
        energy_plot.draw(window);

        window.display();
    }

    return 0;
}
