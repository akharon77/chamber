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

    if (m_pos.x < -EPS || m_pos.x + 2 * getLinearSize() > m_chamber->getWidth())
        m_vel.x = -m_vel.x;

    if (m_pos.y < -EPS || m_pos.y + 2 * getLinearSize() > m_chamber->getHeight())
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
    Molecule(chamber, weight, pos, vel),
    m_rad(getRadiusByWeight(weight)),
    m_circle(m_rad)
{
    m_circle.setFillColor(sf::Color::Blue);
    m_chamber->addMolecule(this);
}

float CircleMolecule::getRadiusByWeight(float weight)
{
    return weight * 20;
}

void CircleMolecule::update()
{
    Molecule::update();
    m_circle.setPosition(m_chamber->getPos() + m_pos);
}

void CircleMolecule::draw(sf::RenderWindow &window)
{
    window.draw(m_circle);
}

Molecule::MoleculeType CircleMolecule::getType() const
{
    return MoleculeType::CIRCLE;
}

float CircleMolecule::getLinearSize() const
{
    return m_rad;
}

// ========================================== //

SquareMolecule::SquareMolecule(Chamber *chamber, float weight, Vector2f pos, Vector2f vel) :
    Molecule(chamber, weight, pos, vel)
{
    m_square.setFillColor(sf::Color::Red);
    update();

    SquareMolecule *to_push = new SquareMolecule(*this);
    m_chamber->addMolecule(to_push);
}

float SquareMolecule::getSideLenByWeight(float weight)
{
    return weight * 0.5;
}

void SquareMolecule::updateSquare()
{
    m_square.setSize({m_side_len, m_side_len});
    m_square.setPosition(m_chamber->getPos() + m_pos);
}

void SquareMolecule::update()
{
    Molecule::update();
    m_side_len = getSideLenByWeight(m_weight);
    updateSquare();
}

void SquareMolecule::draw(sf::RenderWindow &window)
{
    window.draw(m_square);
}

Molecule::MoleculeType SquareMolecule::getType() const
{
    return MoleculeType::SQUARE;
}

float SquareMolecule::getLinearSize() const
{
    return 1.41 * m_side_len;
}

// ========================================== //

Chamber::Chamber(Vector2f pos, float width, float height, float temp) :
    m_pos      (pos),
    m_width    (width),
    m_height   (height),
    m_temp     (temp),
    m_buf_mols (1),
    m_mols     (&m_buf_mols)
{
    m_rect.setFillColor(sf::Color::Black);
    m_rect.setOutlineColor(sf::Color::White);
    m_rect.setOutlineThickness(3);

    updateRect();
}

void Chamber::updateRect()
{
    m_rect.setPosition(m_pos);
    m_rect.setSize({m_width, m_height});
}

void Chamber::updateMolsPos()
{
    int32_t anch = m_mols.GetHead();
    for (int32_t i = 0; i < m_mols.GetSize(); ++i)
    {
        Node<Molecule*> node = *m_mols.Get(anch);
        node.val->update();
        anch = node.next;
    }
}

void Chamber::updateCollisions()
{
    bool flag = true;
    int32_t anch1 = m_mols.GetHead();
    Node<Molecule*> node1 = *m_mols.Get(anch1);

    int32_t i = 0;
    while (flag)
    {
        flag = false;
        int32_t anch2 = node1.next;

        for (int32_t j = 0; j < m_mols.GetSize() - i - 1; ++j)
        {
            Node<Molecule*> node2 = *m_mols.Get(anch2);

            bool isColl = handleCollision(node1.val, node2.val);
            if (isColl)
            {
                delete node1.val;
                delete node2.val;

                m_mols.Erase(anch1);
                m_mols.Erase(anch2);

                flag = true;
                anch1 = m_mols.Get(m_mols.GetHead())->prev;
                break;
            }
            
            anch2 = node2.next;
        }

        anch1 = node1.next;
    }
}

bool Chamber::handleCollision(Molecule *mol1, Molecule *mol2)
{
    if (len(mol2->getPos() - mol1->getPos()) > mol1->getLinearSize() + mol2->getLinearSize())
        return false;

    if (mol1->getType() == 0 && mol2->getType() == 0)
        return collideCC(mol1, mol2);

    // static const bool (Chamber::*)(Molecule*, Molecule*) TABLE[2][2] =
    //     {
    //         {collideCC, collideCR},
    //         {collideRC, collideRR}
    //     };

    // return TABLE[mol1->getType()][mol2->getType()](mol1, mol2);
}

bool Chamber::collideCR(Molecule *mol1, Molecule *mol2) {}
bool Chamber::collideRC(Molecule *mol1, Molecule *mol2) {}
bool Chamber::collideRR(Molecule *mol1, Molecule *mol2) {}

bool Chamber::collideCC(Molecule *mol1, Molecule *mol2)
{
    if (mol1->getWeight() == 1 && mol2->getWeight() == 1)
    {
        SquareMolecule tmp
        (
            this, 
            2, 
            0.5f * (mol1->getPos() + mol2->getPos()),
            0.5f * (mol1->getVelocity() + mol2->getVelocity())
        );

        return true;
    }

    return false;
}

void Chamber::update()
{
    updateMolsPos();
    updateCollisions();
}

void Chamber::draw(sf::RenderWindow &window)
{
    window.draw(m_rect);

    int32_t anch = m_mols.GetHead();

    for (int32_t i = 0; i < m_mols.GetSize(); ++i)
    {
        Node<Molecule*> node = *m_mols.Get(anch);
        node.val->draw(window);
        anch = node.next;
    }
}

void Chamber::addMolecule(Molecule *mol)
{
    m_mols.PushBack(mol);
}

