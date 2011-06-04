#pragma once

#include <string>
#include <QTime>

namespace SingleGame
{
   struct Point
   {
      unsigned int x;
      unsigned int y;
   }; // struct Point

   struct CPlayer
   {
      static unsigned int GenerationID()
      {
         static unsigned int id = 0;
         return ++id;
      }

      std::string m_name;
      unsigned int m_ID;
   }; // struct CPlayer

   struct CPlanet
   {
      CPlayer* m_pPlayer;
      Point m_coordinates;
      unsigned int m_radius;
      double m_countFleet;

      QTime m_timeLastUpdate;
   }; // struct CPlanet

   struct CFleet
   {
      CPlayer* m_pPlayer;
      CPlanet* m_fromPlanet;
      CPlanet* m_toPlanet;

      QTime m_timeStartMove;
   }; // struct CFleet

} // namespace SingleGame
