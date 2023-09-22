#include "molecule.hpp"

Molecule::Molecule(Chamber *chamber, float weight, Vector2f pos, Vector2f vel) :
    m_chamber(chamber),
    m_weight(weight),
    m_pos(pos),
    m_vel(vel)
{}

void Molecule::update()
{
    m_pos += m_vel;
    
    if (m_pos.x < -EPS || m_pos.x > m_chamber->getWidth() + EPS)
        m_vel.x = -m_vel.x;

    if (m_pos.y < -EPS || m_pos.y > m_chamber->getHeight() + EPS)
        m_vel.y = -m_vel.y;
}

void Molecule::setPos(const Vector2f &pos)
{
    m_pos = pos;
}

Vector2f Molecule::getPos() const
{
    return m_pos;
}

void Molecule::setVelocity(const Vector2f &vel)
{
    m_vel = vel;
}

Vector2f Molecule::getVelocity() const
{
    return m_vel;
}

void Molecule::setWeight(float weight)
{
    m_weight = weight;
}

float Molecule::getWeight() const
{
    return m_weight;
}

// ========================================== //

Vector2f Chamber::getPos() const
{
    return m_pos;
}

float Chamber::getWidth() const
{
    return m_width;
}

float Chamber::getHeight() const
{
    return m_height;
}

// ========================================== //

CircleMolecule::CircleMolecule(Chamber *chamber, float weight, Vector2f pos, Vector2f vel) :
    Molecule(chamber, weight, pos, vel)
{
    m_circle.setFillColor(sf::Color::Blue);
    updateCircle();
}

float CircleMolecule::getRadiusByWeight(float weight)
{
    return weight * 0.5;
}

void CircleMolecule::updateCircle()
{
    m_rad = getRadiusByWeight(m_weight);
    m_circle.setRadius(m_rad);
    m_circle.setPosition(m_chamber->getPos() + m_pos);
}

void CircleMolecule::draw(sf::RenderWindow &window)
{
    updateCircle();
    window.draw(m_circle);
}

Molecule::MoleculeType CircleMolecule::getType() const
{
    return MoleculeType::CIRCLE;
}

// ========================================== //

SquareMolecule::SquareMolecule(Chamber *chamber, float weight, Vector2f pos, Vector2f vel) :
    Molecule(chamber, weight, pos, vel)
{
    m_square.setFillColor(sf::Color::Red);
    updateSquare();
}

float SquareMolecule::getSideLenByWeight(float weight)
{
    return weight * 0.5;
}

void SquareMolecule::updateSquare()
{
    m_side_len = getSideLenByWeight(m_weight);
    m_square.setSize({m_side_len, m_side_len});
    m_square.setPosition(m_chamber->getPos() + m_pos);
}

void SquareMolecule::draw(sf::RenderWindow &window)
{
    updateSquare();
    window.draw(m_square);
}

Molecule::MoleculeType SquareMolecule::getType() const
{
    return MoleculeType::SQUARE;
}

// ========================================== //

