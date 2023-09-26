#include "chamber_btn_ctrl.hpp"

const char*    TEMP_TXTRS_PATH      = "temp_texture.png";
const int32_t  TEMP_CTRL_BTN_WIDTH  = 57;
const int32_t  TEMP_CTRL_BTN_HEIGHT = 52;
const Vector2u TEMP_CTRL_DEF_POS    = {0, 0};

const char*    PISTON_TXTRS_PATH      = "piston_texture.png";
const int32_t  PISTON_CTRL_BTN_WIDTH  = 57;
const int32_t  PISTON_CTRL_BTN_HEIGHT = 52;
const Vector2u PISTON_CTRL_DEF_POS    = {0, 0};

const char*    MOLS_TXTRS_PATH      = "mols_ctrl_texture.png";
const int32_t  MOLS_CTRL_BTN_WIDTH  = 57;
const int32_t  MOLS_CTRL_BTN_HEIGHT = 52;
const Vector2u MOLS_CTRL_DEF_POS    = {0, 0};

AssetsManager::AssetsManager()
{
    m_temp_textures.loadFromFile(TEMP_TXTRS_PATH);
    m_pist_textures.loadFromFile(PISTON_TXTRS_PATH);
    m_mols_textures.loadFromFile(MOLS_TXTRS_PATH);
}

const sf::Texture& AssetsManager::getTempCtrlTexture() const
{
    return m_temp_textures;
}

const sf::Texture& AssetsManager::getPistonCtrlTexture() const
{
    return m_pist_textures;
}

const sf::Texture& AssetsManager::getMolsCtrlTexture() const
{
    return m_mols_textures;
}

ChamberTemperatureBtnCtrl::ChamberTemperatureBtnCtrl(Vector2f pos, Chamber *chamber, float delta, AssetsManager *assets) :
    Button
        (
            pos,
            TEMP_CTRL_BTN_WIDTH,
            TEMP_CTRL_BTN_HEIGHT,
            assets->getTempCtrlTexture(),
            TEMP_CTRL_DEF_POS,
            TEMP_CTRL_DEF_POS + Vector2u{0,     TEMP_CTRL_BTN_HEIGHT},
            TEMP_CTRL_DEF_POS + Vector2u{0, 2 * TEMP_CTRL_BTN_HEIGHT}
        ), 
    m_chamber (chamber),
    m_delta   (delta)
{
    if (m_delta > 0)
    {
        m_default_pos.x += TEMP_CTRL_BTN_WIDTH;
        m_pressed_pos.x += TEMP_CTRL_BTN_WIDTH;
        m_focused_pos.x += TEMP_CTRL_BTN_WIDTH;
        m_sprite.setTextureRect(sf::IntRect(m_default_pos.x, m_default_pos.y, m_width, m_height));
    }

}

void ChamberTemperatureBtnCtrl::onPressed()
{
    m_chamber->updTemperature(m_delta);
}

void ChamberTemperatureBtnCtrl::onReleased() {};
void ChamberTemperatureBtnCtrl::onFocused()  {};

ChamberPistonBtnCtrl::ChamberPistonBtnCtrl(Vector2f pos, Chamber *chamber, float delta, AssetsManager *assets) :
    Button
        (
            pos,
            PISTON_CTRL_BTN_WIDTH,
            PISTON_CTRL_BTN_HEIGHT,
            assets->getPistonCtrlTexture(),
            PISTON_CTRL_DEF_POS,
            PISTON_CTRL_DEF_POS + Vector2u{0,     PISTON_CTRL_BTN_HEIGHT},
            PISTON_CTRL_DEF_POS + Vector2u{0, 2 * PISTON_CTRL_BTN_HEIGHT}
        ), 
    m_chamber (chamber),
    m_delta   (delta)
{
    if (m_delta > 0)
    {
        m_default_pos.x += PISTON_CTRL_BTN_WIDTH;
        m_pressed_pos.x += PISTON_CTRL_BTN_WIDTH;
        m_focused_pos.x += PISTON_CTRL_BTN_WIDTH;
        m_sprite.setTextureRect(sf::IntRect(m_default_pos.x, m_default_pos.y, m_width, m_height));
    }

}

void ChamberPistonBtnCtrl::onPressed()
{
    m_chamber->updPiston(m_delta);
}

void ChamberPistonBtnCtrl::onReleased() {};
void ChamberPistonBtnCtrl::onFocused()  {};

ChamberMolsBtnCtrl::ChamberMolsBtnCtrl(Vector2f pos, Chamber *chamber, Molecule::MoleculeType type, int32_t delta, AssetsManager *assets) :
    Button
        (
            pos,
            MOLS_CTRL_BTN_WIDTH,
            MOLS_CTRL_BTN_HEIGHT,
            assets->getMolsCtrlTexture(),
            MOLS_CTRL_DEF_POS,
            MOLS_CTRL_DEF_POS + Vector2u{0,     MOLS_CTRL_BTN_HEIGHT},
            MOLS_CTRL_DEF_POS + Vector2u{0, 2 * MOLS_CTRL_BTN_HEIGHT}
        ), 
    m_chamber (chamber),
    m_type    (type),
    m_delta   (delta)
{
    if (m_type == Molecule::MoleculeType::SQUARE)
    {
        m_default_pos.x += MOLS_CTRL_BTN_WIDTH;
        m_pressed_pos.x += MOLS_CTRL_BTN_WIDTH;
        m_focused_pos.x += MOLS_CTRL_BTN_WIDTH;
        m_sprite.setTextureRect(sf::IntRect(m_default_pos.x, m_default_pos.y, m_width, m_height));
    }

}

void ChamberMolsBtnCtrl::onPressed()
{
    for (int32_t i = 0; i < m_delta; ++i)
    {
        Vector2f vel = {rand(), rand()};
        vel /= len(vel);

        switch (m_type)
        {
            case Molecule::MoleculeType::CIRCLE:
                m_chamber->addMolecule
                (
                    new CircleMolecule
                    {
                        1,
                        0.5f * Vector2f{m_chamber->getWidth(), m_chamber->getHeight()},
                        vel
                    }
                );
                break;
            case Molecule::MoleculeType::SQUARE:
                m_chamber->addMolecule
                (
                    new SquareMolecule 
                    {
                        1,
                        0.5f * Vector2f{m_chamber->getWidth(), m_chamber->getHeight()},
                        vel
                    }
                );
                break;
        }
    }
}

void ChamberMolsBtnCtrl::onReleased() {};
void ChamberMolsBtnCtrl::onFocused()  {};

