#ifndef CHAMBER_BTN_CTRL_HPP
#define CHAMBER_BTN_CTRL_HPP

class AssetsManager
{
    sf::Texture m_temperatue_textures;

public:
    AssetsManager();

    ~AssertsManager() = default;
    AssetsManager(const AssetsManager &rhs) = delete;
    AssetsManager& operator = (const AssetsManager &rhs) = delete;
};

class ChamberTemperatueBtnCtrl : public Button
{
    
};

#endif  // CHAMBER_BTN_CTRL_HPP
