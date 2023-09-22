#ifndef MOLECULE_HPP
#define MOLECULE_HPP

#include <SFML/Graphics.hpp>

#include "vector2f.hpp"
#include "list.hpp"

class Chamber;

class Molecule
{
protected:
    enum MoleculeType
    {
        CIRCLE,
        SQUARE
    };

    Chamber *m_chamber;

    float m_weight;

    Vector2f m_pos;
    Vector2f m_vel;
    
public:
    Molecule() = delete;

    Molecule(Chamber *chamber, float weight = 0, Vector2f pos = {0, 0}, Vector2f vel = {0, 0});

    Molecule(const Molecule &rhs)              = default;
    Molecule& operator = (const Molecule &rhs) = default;
    ~Molecule()                                = default;

    void     setPos(const Vector2f &pos);
    Vector2f getPos() const;

    void     setVelocity(const Vector2f &vel);
    Vector2f getVelocity() const;

    void  setWeight(float weight);
    float getWeight() const;

    virtual void update();

    virtual void draw(sf::RenderWindow &window) = 0;

    virtual Molecule::MoleculeType getType() const = 0;
};

class Chamber
{
    Vector2f m_pos;

    float    m_width;
    float    m_height;

    float    m_temp;
    float    m_prss;

    List<Molecule*> m_mols;

public:
    Chamber() = default;
    Chamber(const Chamber &chamber) = default;
    Chamber& operator = (const Chamber &chamber) = default;
    ~Chamber() = default;

    Vector2f getPos()    const;
    float    getWidth()  const;
    float    getHeight() const;
};

// ========================================== //

class CircleMolecule : public Molecule
{
    float m_rad;
    sf::CircleShape m_circle;

    static float getRadiusByWeight(float weight);

    void updateCircle();

public:
    CircleMolecule(Chamber *chamber, float weight = 0, Vector2f pos = {0, 0}, Vector2f vel = {0, 0});

    CircleMolecule(const CircleMolecule &rhs)              = default;
    CircleMolecule& operator = (const CircleMolecule &rhs) = default;
    ~CircleMolecule()                                      = default;

    virtual void draw(sf::RenderWindow &window) override;

    virtual Molecule::MoleculeType getType() const override;
};

// ========================================== //

class SquareMolecule : public Molecule
{
    float m_side_len;
    sf::RectangleShape m_square;

    static float getSideLenByWeight(float weight);

    void updateSquare();

public:
    SquareMolecule(Chamber *chamber, float weight = 0, Vector2f pos = {0, 0}, Vector2f vel = {0, 0});

    SquareMolecule(const SquareMolecule &rhs)              = default;
    SquareMolecule& operator = (const SquareMolecule &rhs) = default;
    ~SquareMolecule()                                      = default;

    virtual void draw(sf::RenderWindow &window) override;

    virtual Molecule::MoleculeType getType() const override;
};

#endif  // MOLECULE_HPP

