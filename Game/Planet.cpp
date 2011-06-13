/// @file Fleet.cpp
/// @author Dmitriy Kozhevnikov
/// @date 06-06-2011

#include <cmath>
#include "Planet.h"

//const double EPS = 0.5;

namespace Game
{
   CPlanet::CPlanet(const unsigned short id, const unsigned short x, const unsigned short y,
                    const unsigned short radius, const unsigned long army,
                    const unsigned short playerId):
      m_id(id),
      m_x(x),
      m_y(y),
      m_radius(10 + radius + radius / 10),
      m_growth(radius),
      m_army(army),
      m_playerId(playerId)
   {
   }

   unsigned long CPlanet::GetArmy() const
   {
      return floor(m_army);
   }

   unsigned short CPlanet::GetPlayerId() const
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

   unsigned int CPlanet::GetGrowth() const
   {
      return m_growth;
   }

   void CPlanet::SetArmy(const unsigned long army)
   {
      m_army = army;
   }

   void CPlanet::SetPlayer(const unsigned short playerId)
   {
      m_playerId = playerId;
   }
   void CPlanet::UpdateArmy(const double army)
   {
      m_army += army;
   }
} // Namespace Game
