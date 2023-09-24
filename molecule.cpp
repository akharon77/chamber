#include "molecule.hpp"

Molecule::Molecule(float weight, Vector2f pos, Vector2f vel) :
    m_weight(weight),
    m_pos(pos),
    m_vel(vel)
{}

void Molecule::update()
{
    m_pos += m_vel;
}

void Molecule::setChamber(Chamber *chamber)
{
    m_chamber = chamber;
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

CircleMolecule::CircleMolecule(float weight, Vector2f pos, Vector2f vel) :
    Molecule(weight, pos, vel),
    m_rad(getRadiusByWeight(weight)),
    m_circle(m_rad)
{
    m_circle.setFillColor(sf::Color::Blue);
    m_circle.setOrigin(m_rad, m_rad);
}

float CircleMolecule::getRadiusByWeight(float weight)
{
    return weight * 10;
}

void CircleMolecule::updateCircle()
{
    m_circle.setPosition(m_chamber->getPos() + m_pos);
}

void CircleMolecule::update()
{
    Molecule::update();
    updateCircle();
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

SquareMolecule::SquareMolecule(float weight, Vector2f pos, Vector2f vel) :
    Molecule(weight, pos, vel),
    m_side_len(getSideLenByWeight(weight)),
    m_square({m_side_len, m_side_len})
{
    m_square.setFillColor(sf::Color::Red);
    m_square.setOrigin(0.5 * m_side_len, 0.5 * m_side_len);
}

float SquareMolecule::getSideLenByWeight(float weight)
{
    return weight * 20;
}

void SquareMolecule::updateSquare()
{
    m_square.setPosition(m_chamber->getPos() + m_pos);
}

void SquareMolecule::update()
{
    Molecule::update();
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
    return 0.5 * m_side_len;
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
        Molecule *mol = node.val;

        mol->update();
        if (mol->m_pos.x - mol->getLinearSize() < -EPS || mol->m_pos.x + mol->getLinearSize() > m_width)
            mol->m_vel.x *= -1;

        if (mol->m_pos.y - mol->getLinearSize() < -EPS || mol->m_pos.y + mol->getLinearSize() > m_height)
            mol->m_vel.y *= -1;;
    
        anch = node.next;
    }
}

void Chamber::updateCollisions()
{
    int32_t i = 0;
    int32_t anch1 = m_mols.GetHead();
    Node<Molecule*> node1 = *m_mols.Get(anch1);

    bool flag = true;
    while (flag)
    {
        flag = false;

        int32_t anch2 = node1.next;
        Node<Molecule*> node2 = *m_mols.Get(anch2);

        bool isColl = false;
        for (int32_t j = 0; j < m_mols.GetSize() - i - 1; ++j)
        {
            isColl = handleCollision(node1.val, node2.val);
            if (isColl)
            {
                delete node1.val;
                delete node2.val;

                m_mols.Erase(anch1);
                m_mols.Erase(anch2);

                flag = true;
                break;
            }
            
            anch2 = node2.next;
            node2 = *m_mols.Get(anch2);
        }

        if (isColl)
        {
            anch1 = m_mols.GetHead();
            node1 = *m_mols.Get(anch1);
            i = 0;
        }
        else
        {
            anch1 = node1.next;
            node1 = *m_mols.Get(anch1);
            ++i;
        }
    }
}

bool Chamber::handleCollision(Molecule *mol1, Molecule *mol2)
{
    if (len(mol2->getPos() - mol1->getPos()) > mol1->getLinearSize() + mol2->getLinearSize())
        return false;

    if (mol1->getType() == 0 && mol2->getType() == 0)
        return collideCC(mol1, mol2);

    return false;

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
        addMolecule(new SquareMolecule
            {
                2, 
                0.5f * (mol1->getPos() + mol2->getPos()),
                0.5f * (mol1->getVelocity() + mol2->getVelocity())
            }
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
    mol->setChamber(this);
    m_mols.PushBack(mol);
}

