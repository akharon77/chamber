#ifndef CHAMBER_BTN_CTRL_HPP
#define CHAMBER_BTN_CTRL_HPP

#include "button.hpp"
#include "molecule.hpp"

class AssetsManager
{
    sf::Texture m_temp_textures;
    sf::Texture m_pist_textures;
    sf::Texture m_mols_textures;
public:
    AssetsManager();

    const sf::Texture& getTempCtrlTexture  () const;
    const sf::Texture& getPistonCtrlTexture() const;
    const sf::Texture& getMolsCtrlTexture  () const;

    AssetsManager(const AssetsManager &rhs) = delete;
    AssetsManager& operator = (const AssetsManager &rhs) = delete;
    ~AssetsManager() = default;
};

class ChamberTemperatureBtnCtrl : public Button
{
    Chamber *m_chamber;
    float    m_delta;

public:
    ChamberTemperatureBtnCtrl(Vector2f pos, Chamber *chamber, float delta, AssetsManager *assets);

    ChamberTemperatureBtnCtrl(const ChamberTemperatureBtnCtrl &rhs) = delete;
    ChamberTemperatureBtnCtrl& operator = (const ChamberTemperatureBtnCtrl &rhs) = delete;
    ~ChamberTemperatureBtnCtrl() = default;

    virtual void onPressed()  override;
    virtual void onReleased() override;
    virtual void onFocused()  override;
};

class ChamberPistonBtnCtrl : public Button
{
    Chamber *m_chamber;
    float    m_delta;

public:
    ChamberPistonBtnCtrl(Vector2f pos, Chamber *chamber, float delta, AssetsManager *assets);

    ChamberPistonBtnCtrl(const ChamberPistonBtnCtrl &rhs) = delete;
    ChamberPistonBtnCtrl& operator = (const ChamberPistonBtnCtrl &rhs) = delete;
    ~ChamberPistonBtnCtrl() = default;

    virtual void onPressed()  override;
    virtual void onReleased() override;
    virtual void onFocused()  override;
};

class ChamberMolsBtnCtrl : public Button
{
    Chamber *m_chamber;

    Molecule::MoleculeType m_type;
    int32_t  m_delta;

public:
    ChamberMolsBtnCtrl(Vector2f pos, Chamber *chamber, Molecule::MoleculeType type, int32_t delta, AssetsManager *assets);

    ChamberMolsBtnCtrl(const ChamberMolsBtnCtrl &rhs) = delete;
    ChamberMolsBtnCtrl& operator = (const ChamberMolsBtnCtrl &rhs) = delete;
    ~ChamberMolsBtnCtrl() = default;

    virtual void onPressed()  override;
    virtual void onReleased() override;
    virtual void onFocused()  override;
};

#endif  // CHAMBER_BTN_CTRL_HPP

