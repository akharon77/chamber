#ifndef MOLECULE_HPP
#define MOLECULE_HPP

#include <SFML/Graphics.hpp>

#include "vector2f.hpp"
#include "list.hpp"

class Molecule;

class Chamber
{
    Vector2f m_pos;

    float    m_width;
    float    m_height;

    float    m_temp;
    int32_t  m_pressure;

    BufferList<Molecule*> m_buf_mols;
    List<Molecule*>       m_mols;

    sf::RectangleShape m_rect;

    void updateRect();
    void updateMolsPos();
    void updateCollisions();
    bool handleCollision(Molecule *mol1, Molecule *mol2);

    bool collideCC(Molecule *mol1, Molecule *mol2);
    bool collideCR(Molecule *mol1, Molecule *mol2);
    bool collideRC(Molecule *mol1, Molecule *mol2);
    bool collideRR(Molecule *mol1, Molecule *mol2);

public:
    Chamber(Vector2f pos = {0, 0}, float width = 0, float height = 0, float temp = 100);

    Chamber(const Chamber &chamber) = delete;
    Chamber& operator = (const Chamber &chamber) = delete;
    ~Chamber() = default;

    void update();
    void draw(sf::RenderWindow &window);

    Vector2f getPos()      const;
    float    getWidth()    const;
    float    getHeight()   const;
    int32_t  getPressure() const;

    void addMolecule(Molecule *mol);
};

// ========================================== //

class Molecule
{
    friend class Chamber;

protected:
    enum MoleculeType
    {
        CIRCLE,
        SQUARE
    };

    Chamber *m_chamber;

    int32_t m_weight;

    Vector2f m_pos;
    Vector2f m_vel;
    
public:
    Molecule() = delete;

    Molecule(float weight = 0, Vector2f pos = {0, 0}, Vector2f vel = {0, 0});

    Molecule(const Molecule &rhs)              = default;
    Molecule& operator = (const Molecule &rhs) = default;
    ~Molecule()                                = default;

    void setChamber(Chamber *chamber);

    void     setPos(const Vector2f &pos);
    Vector2f getPos() const;

    void     setVelocity(const Vector2f &vel);
    Vector2f getVelocity() const;

    void  setWeight(int32_t weight);
    int32_t getWeight() const;

    virtual void update();

    virtual void draw(sf::RenderWindow &window) = 0;

    virtual Molecule::MoleculeType getType() const = 0;
    virtual float getLinearSize() const = 0;
};

// ========================================== //

class CircleMolecule : public Molecule
{
    float m_rad;
    sf::CircleShape m_circle;

    static float getRadiusByWeight(float weight);

    void updateCircle();

public:
    CircleMolecule(float weight = 0, Vector2f pos = {0, 0}, Vector2f vel = {0, 0});

    CircleMolecule(const CircleMolecule &rhs)              = default;
    CircleMolecule& operator = (const CircleMolecule &rhs) = default;
    ~CircleMolecule()                                      = default;

    virtual void draw(sf::RenderWindow &window) override;

    virtual Molecule::MoleculeType getType() const override;
    virtual float getLinearSize() const override;
    
    virtual void update() override;
};

// ========================================== //

class SquareMolecule : public Molecule
{
    float m_side_len;
    sf::RectangleShape m_square;

    static float getSideLenByWeight(float weight);

    void updateSquare();

public:
    SquareMolecule(float weight = 0, Vector2f pos = {0, 0}, Vector2f vel = {0, 0});

    SquareMolecule(const SquareMolecule &rhs)              = default;
    SquareMolecule& operator = (const SquareMolecule &rhs) = default;
    ~SquareMolecule()                                      = default;

    virtual void draw(sf::RenderWindow &window) override;

    virtual Molecule::MoleculeType getType() const override;
    virtual float getLinearSize() const override;

    virtual void update() override;
};

#endif  // MOLECULE_HPP

