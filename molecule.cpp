#include <cmath>

#include "molecule.hpp"

const int32_t CNT_UPD_AVER = 2000;

const float TEMP_K_CONST = 2.1;

const float PISTON_FOOT_WIDTH = 10;
const float PISTON_HAND_HEIGHT = 5;

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

void Molecule::setWeight(int32_t weight)
{
    m_weight = weight;
}

int32_t Molecule::getWeight() const
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

float Chamber::getPressure() const
{
    return m_pressure / m_cnt_upd;
}

float Chamber::getPistonHeight() const
{
    return m_piston_height;
}

float Chamber::getEnergy()
{
    float res = 0;

    int32_t anch = m_mols.GetHead();
    Node<Molecule*> node = *m_mols.Get(anch);

    for (int32_t i = 0; i < m_mols.GetSize(); ++i)
    {
        Molecule *mol = node.val;

        res += 0.5 * mol->m_weight * dot(mol->m_vel, mol->m_vel);
            
        anch = node.next;
        node = *m_mols.Get(anch);
    }

    return res;
}

void Chamber::updTemperature(float delta)
{
    m_temperature += delta;

    if (m_temperature < 10)
        m_temperature = 10;
}

void Chamber::updPiston(float delta)
{
    m_piston_height -= delta;

    if (m_piston_height > m_height)
        m_piston_height = m_height;

    if (m_piston_height < PISTON_HAND_HEIGHT)
        m_piston_height = PISTON_HAND_HEIGHT;

    updatePiston();
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
    return 30 - exp(-0.2f * weight + 2.7);
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
    return 30 - exp(-0.9f * weight + 2.7);
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

Chamber::Chamber(Vector2f pos, float width, float height, float temperature) :
    m_pos           (pos),
    m_piston_height (PISTON_HAND_HEIGHT),
    m_width         (width),
    m_height        (height),
    m_temperature   (temperature),
    m_buf_mols      (1),
    m_mols          (&m_buf_mols),
    m_cnt_upd       (0)
{
    m_rect.setFillColor(sf::Color::Black);
    m_rect.setOutlineColor(sf::Color::White);
    m_rect.setOutlineThickness(3);

    m_piston_foot.setFillColor(sf::Color::White);
    m_piston_hand.setFillColor(sf::Color::White);

    updateRect();
    updatePiston();
}

void Chamber::updateRect()
{
    m_rect.setPosition(m_pos);
    m_rect.setSize({m_width, m_height});
}

void Chamber::updatePiston()
{
    m_piston_foot.setPosition(m_pos + 0.5f * Vector2f{m_width - PISTON_FOOT_WIDTH, 0});
    m_piston_foot.setSize({PISTON_FOOT_WIDTH, m_piston_height});
    
    m_piston_hand.setPosition(m_pos + Vector2f{0, m_piston_height - PISTON_HAND_HEIGHT});
    m_piston_hand.setSize({m_width, PISTON_HAND_HEIGHT});
}

void Chamber::updateMolsPos()
{
    int32_t anch = m_mols.GetHead();
    Node<Molecule*> node = *m_mols.Get(anch);

    ++m_cnt_upd;
    if (m_cnt_upd > CNT_UPD_AVER)
    {
        m_cnt_upd = 1;
        m_pressure = 0;
    }

    for (int32_t i = 0; i < m_mols.GetSize(); ++i)
    {
        Molecule *mol = node.val;

        mol->update();
        float linear_size = mol->getLinearSize();

        bool is_coll = false;

        if (mol->m_pos.x - linear_size < -EPS)
        {
            mol->m_pos.x = linear_size + EPS;
            mol->m_vel.x *= -1;
            m_pressure += abs(mol->m_vel.x) * mol->m_weight;
            is_coll = true;
        }

        if (mol->m_pos.x + linear_size > m_width)
        {
            mol->m_pos.x = m_width - linear_size - EPS;
            mol->m_vel.x *= -1;
            m_pressure += abs(mol->m_vel.x) * mol->m_weight;
            is_coll = true;
        }
            
        if (mol->m_pos.y - linear_size < m_piston_height - EPS)
        {
            mol->m_pos.y = m_piston_height + linear_size + EPS;
            mol->m_vel.y *= -1;;
            m_pressure += abs(mol->m_vel.y) * mol->m_weight;
            is_coll = true;
        }
    
        if (mol->m_pos.y + mol->getLinearSize() > m_height)
        {
            mol->m_pos.y = m_height - linear_size - EPS;
            mol->m_vel.y *= -1;;
            m_pressure += abs(mol->m_vel.y) * mol->m_weight;
            is_coll = true;
        }

        if (is_coll)
            mol->m_vel *= (float) (2 * sqrtf(m_temperature / mol->m_weight) / len(mol->m_vel));
            
        anch = node.next;
        node = *m_mols.Get(anch);
    }
}

void Chamber::updateCollisions()
{
    int32_t i = 0;
    int32_t anch1 = m_mols.GetHead();
    Node<Molecule*> node1 = *m_mols.Get(anch1);

    int32_t size = m_mols.GetSize();

    for (int32_t i = 0; i < size - 1; ++i)
    {
        int32_t anch2 = node1.next;
        Node<Molecule*> node2 = *m_mols.Get(anch2);

        for (int32_t j = 0; j < size - i - 1; ++j)
        {
            bool isColl = handleCollision(node1.val, node2.val);
            if (isColl)
            {
                delete node1.val;
                delete node2.val;

                m_mols.Erase(anch1);
                m_mols.Erase(anch2);

                return;
            }
            
            anch2 = node2.next;
            node2 = *m_mols.Get(anch2);
        }

        anch1 = node1.next;
        node1 = *m_mols.Get(anch1);
    }
}

typedef bool (Chamber::*func_collide_t)(Molecule* mol1, Molecule* mol2);

bool Chamber::handleCollision(Molecule *mol1, Molecule *mol2)
{
    Vector2f prev_pos1 = mol1->getPos() - mol1->getVelocity();
    Vector2f prev_pos2 = mol2->getPos() - mol2->getVelocity();

    if (len(mol1->getPos() - mol2->getPos()) > mol1->getLinearSize() + mol2->getLinearSize())
        return false;

    if (len(mol1->getPos() - mol2->getPos()) > len(prev_pos1 - prev_pos2))
        return false;

    static const func_collide_t TABLE[2][2] =
        {
            {&Chamber::collideCC, &Chamber::collideCR},
            {&Chamber::collideRC, &Chamber::collideRR}
        };

    return (this->*TABLE[mol1->getType()][mol2->getType()])(mol1, mol2);
}

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

bool Chamber::collideCR(Molecule *mol1, Molecule *mol2)
{
    if (mol1->getWeight() == 1)
    {
        addMolecule(new SquareMolecule
            {
                mol2->getWeight() + 1, 
                0.5f * (mol1->getPos() + mol2->getPos()),
                (mol1->getVelocity() + (float) mol2->getWeight() * mol2->getVelocity()) / (mol2->getWeight() + 1.f)
            }
        );

        return true;
    }

    return false;
}

bool Chamber::collideRC(Molecule *mol1, Molecule *mol2)
{
    if (mol2->getWeight() == 1)
    {
        addMolecule(new SquareMolecule
            {
                mol1->getWeight() + 1, 
                0.5f * (mol1->getPos() + mol2->getPos()),
                (mol2->getVelocity() + (float) mol1->getWeight() * mol1->getVelocity()) / (mol1->getWeight() + 1.f)
            }
        );

        return true;
    }

    return false;
}

bool Chamber::collideRR(Molecule *mol1, Molecule *mol2)
{
    Vector2f mid_pos = 0.5f * (mol1->getPos() + mol2->getPos());

    int32_t wgh1 = mol1->getWeight();
    int32_t wgh2 = mol2->getWeight();

    float alpha_k = 2 * M_PI / (wgh1 + wgh2 - 1);
    float curr_alpha = 0;
    for (int32_t i = 0; i < wgh1 + wgh2 - 1; ++i, curr_alpha += alpha_k)
    {
        addMolecule(new CircleMolecule
            {
                1, 
                mid_pos,
                Vector2f(cos(curr_alpha), sin(curr_alpha))
            }
        );
    }
    
    addMolecule(new CircleMolecule
        {
            1, 
            mid_pos,
            (float) wgh1 * mol1->getVelocity() + (float) wgh2 * mol2->getVelocity()
        }
    );

    return true;
}

void Chamber::update()
{
    updateMolsPos();
    updateCollisions();
}

void Chamber::draw(sf::RenderWindow &window)
{
    window.draw(m_rect);
    window.draw(m_piston_foot);
    window.draw(m_piston_hand);

    int32_t anch = m_mols.GetHead();
    Node<Molecule*> node = *m_mols.Get(anch);

    int32_t size = m_mols.GetSize();
    for (int32_t i = 0; i < size; ++i)
    {
        node.val->draw(window);
        anch = node.next;
        node = *m_mols.Get(anch);
    }
}

void Chamber::addMolecule(Molecule *mol)
{
    mol->setChamber(this);
    m_mols.PushBack(mol);
}

