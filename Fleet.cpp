#include "Fleet.h"
#include "Planet.h"

CFleet::CFleet(unsigned short id, CPlanet* from, CPlanet* to, unsigned int playerId, unsigned long number, double percent):
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
   updatePosition();
}

void CFleet::IncreaseProcent(double i_incOn)
{
   this->SetPercent(m_percentPassed + i_incOn);
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
