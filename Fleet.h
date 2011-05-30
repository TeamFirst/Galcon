#pragma once

class CPlanet;

class CFleet
{
public:
   CFleet(unsigned short id, CPlanet* from, CPlanet* to,
          unsigned int playerId, unsigned long number, double percent);

   void SetPercent(unsigned short); //For synhronization with server

   void IncreaseProcent(double); //For simulation

   //Output into GUI
   void GetPosition (double&, double&) const;
   unsigned long GetShipCount() const;
   unsigned short GetPlayerId() const;
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
   unsigned long m_number;

   double m_percentPassed;
   double m_actualX;
   double m_actualY;

   bool m_reached;
};

