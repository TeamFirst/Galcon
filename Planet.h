#ifndef CPLANET_H
#define CPLANET_H
#include "Player.h"

class CPlanet
{
public:
   CPlanet(unsigned short, unsigned short, unsigned short, unsigned short, unsigned long, unsigned short);
   ~CPlanet();

   unsigned long GetArmy() const;
   unsigned int GetPlayerId() const;
   void GetPosition(unsigned int&, unsigned int&) const;
   unsigned int GetRadius() const;

   void SetArmy (const unsigned long);
   void SetPlayer (const unsigned int);

private:
   const double EPS = 0.5;

   unsigned short m_id;
   unsigned short m_x;
   unsigned short m_y;
   unsigned short m_radius;
   double m_army;
   unsigned short m_playerId;
};

#endif // CPLANET_H
