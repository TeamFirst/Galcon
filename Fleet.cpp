#include "Fleet.h"

CFleet::CFleet(unsigned short id, CPlanet* from, CPlanet* to, unsigned int playerId, unsigned int number, double percent):
   m_id(id),
   m_from(from),
   m_to(to),
   m_playerId(playerId),
   m_number(number),
   m_percentPassed(percent),
{
   if (m_percentPassed < 100)
   {
      m_reached = false;
   }
   else
   {
      m_reached = true;
   }

   unsigned int x;
   unsigned int y;
   m_from->GetPosition(x, y);
   m_fromPl.x = x;
   m_fromPl.y = y;

   m_to->GetPosition(x, y);
   m_toPl.x = x;
   m_toPl.y = y;

}

void CFleet::GetPosition(unsigned short& o_nX, unsigned short& o_nY) const
{
   o_nX = m_actualX;
   o_nY = m_actualY;
}

void CFleet::GetPlayerId() const
{
   return m_playerId;
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

void CFleet::updatePosition()
{
   m_actualPosition.x = ((double)m_percentPassed/100) * m_toPl.x +
            (1 - (double)m_percentPassed/100) * m_fromPl.x;
   m_actualPosition.y = ((double)m_percentPassed/100) * m_toPl.y +
            (1 - (double)m_percentPassed/100) * m_fromPl.y;
}
