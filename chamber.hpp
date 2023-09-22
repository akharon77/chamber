#ifndef CHAMBER_HPP
#define CHAMBER_HPP

#include "list.hpp"

class Chamber
{
    float m_temp;
    float m_prss;
    List<Molecule*> m_mols;

public:
    Chamber() = default;
    Chamber(const Chamber &chamber) = default;
    Chamber& operator = (const Chamber &chamber) = default;
    ~Chamber() = default;
};

#endif  // CHAMBER_HPP
