#ifndef FLEET_H
#define FLEET_H

#include "Planet.h"
#include "Player.h"

class CFleet
{
public:
   CFleet(unsigned short, CPlanet*, CPlanet*, unsigned int, unsigned int, double);
   ~CFleet();

   void SetPercent(double); //For synhronization with server

   void IncreaseProcent(double); //For simulation

   //Output into GUI
   void GetPosition (double&, double&) const;
   unsigned int GetShipCount();
   unsigned int GetPlayerId();
   bool ReachedDestination() const;

private:
   struct Point
   {
      unsigned int x;
      unsigned int y;
   };

   void updatePosition();

   CPlanet* m_from;
   CPlanet* m_to;
   Point m_fromPl;
   Point m_toPl;

   unsigned int m_playerId;
   unsigned short m_id;
   unsigned short m_number;

   double m_percentPassed;
   double m_actualX;
   double m_actualY;

   bool m_reached;
};

#endif // FLEET_H
