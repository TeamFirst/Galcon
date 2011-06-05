#pragma once

#include "Planet.h"

namespace Game
{
   class CFleet
   {
   public:
      CFleet(unsigned int id, CPlanet* from, CPlanet* to,
             unsigned int playerId, unsigned long number, double percent);

      void SetPercent(const double percent); //For synhronization with server

      void IncreaseWay(double onWay); //For simulation

      //Output into GUI
      void GetPosition (double& x, double& y) const;
      void GetFixedPoint (double& x, double& y) const;

      unsigned long GetShipCount() const;
      unsigned short GetPlayerId() const;
      unsigned int GetId() const;
      bool ReachedDestination() const;

   private:
      struct Point
      {
         unsigned int x;
         unsigned int y;
      };

      void updatePosition();

      unsigned int m_id;
      CPlanet* m_from;
      CPlanet* m_to;
      Point m_fromPl;
      Point m_toPl;

      unsigned int m_playerId;
      unsigned long m_number;

      double m_percentPassed;
      double m_actualX;
      double m_actualY;

      double m_distance;
      bool m_reached;
   };
} // Namespace Game
