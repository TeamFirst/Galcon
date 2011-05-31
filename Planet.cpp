#include <math.h>

#include "Planet.h"

const double EPS = 0.5;

CPlanet::CPlanet(unsigned short id, unsigned short x, unsigned short y,
                 unsigned short radius, unsigned long army,
                 unsigned short playerId):
   m_id(id),
   m_x(x),
   m_y(y),
   m_radius(radius),
   m_army(army),
   m_playerId(playerId)
{
}

unsigned long CPlanet::GetArmy() const
{
   return floor(m_army);
}

unsigned int CPlanet::GetPlayerId() const
{
   return this->m_playerId;
}

unsigned short CPlanet::GetId() const
{
   return m_id;
}

void CPlanet::GetPosition(unsigned int& o_nX, unsigned int& o_nY) const
{
   o_nX = m_x;
   o_nY = m_y;
}

unsigned int CPlanet::GetRadius() const
{
   return m_radius;
}

void CPlanet::SetArmy(const unsigned long army)
{
   m_army = army;
}

void CPlanet::SetPlayer(const unsigned int playerId)
{
   m_playerId = playerId;
}

