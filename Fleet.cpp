#include "Fleet.h"
#include "Planet.h"
#include <cmath>

CFleet::CFleet(unsigned int id, CPlanet* from, CPlanet* to, unsigned int playerId, unsigned long number, double percent):
   m_id(id),
   m_from(from),
   m_to(to),
   m_playerId(playerId),
   m_number(number),
   m_percentPassed(percent)
{
   if (m_percentPassed < 100)
   {
      m_reached = false;
   }
   else
   {
      m_reached = true;
      m_percentPassed = 100;
   }

   unsigned int x;
   unsigned int y;
   m_from->GetPosition(x, y);
   m_fromPl.x = x;
   m_fromPl.y = y;

   m_to->GetPosition(x, y);
   m_toPl.x = x;
   m_toPl.y = y;

   m_distance = sqrt((m_toPl.x - m_fromPl.x) * (m_toPl.x - m_fromPl.x) +
                   (m_toPl.y - m_fromPl.y) * (m_toPl.y - m_fromPl.y));
   updatePosition();
}

void CFleet::GetPosition(double& o_nX, double& o_nY) const
{
   o_nX = m_actualX;
   o_nY = m_actualY;
}

unsigned short CFleet::GetPlayerId() const
{
   return m_playerId;
}

unsigned int CFleet::GetId() const
{
   return m_id;
}

unsigned long CFleet::GetShipCount() const
{
   return m_number;
}

void CFleet::SetPercent(const unsigned short i_nPerc)
{
   m_percentPassed = i_nPerc;
   if (m_percentPassed >= 100)
   {
      m_percentPassed = 100;
      if (!m_reached)
      {
         m_reached = true;
         if (m_to->GetArmy() < m_number)
         {
            m_to->SetPlayer(m_playerId);
            m_to->SetArmy(m_number - m_to->GetArmy());
         }
         else
         {
            m_to->SetArmy(m_to->GetArmy() - m_number);
         }
      }
   }
   updatePosition();
}

void CFleet::IncreaseWay(double onWay)
{
   double onPerc = 100.0 * onWay/m_distance;
   this->SetPercent(m_percentPassed + onPerc);
}

bool CFleet::ReachedDestination() const
{
   return m_reached;
}

void CFleet::updatePosition()
{
   m_actualX = ((double)m_percentPassed/100) * m_toPl.x +
            (1 - (double)m_percentPassed/100) * m_fromPl.x;
   m_actualY = ((double)m_percentPassed/100) * m_toPl.y +
            (1 - (double)m_percentPassed/100) * m_fromPl.y;
}
