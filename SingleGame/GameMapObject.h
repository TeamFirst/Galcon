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

   struct CGameObject
   {
      void GenerationID()
      {
         m_ID = GenerationTypeObjectID();
      }

      unsigned int GetID() const
      {
         return m_ID;
      }

   protected:
      static unsigned int GenerationTypeObjectID()
      {
         static unsigned int sID = 0;
         return ++sID;
      }

      unsigned int m_ID;

   }; // struct CGameObject

   struct CPlayer : public CGameObject
   {
      void SetNeutral()
      {
         CGameObject::m_ID = 0;
      }

      std::string m_name;      
   }; // struct CPlayer

   struct CPlanet : public CGameObject
   {
      CPlayer* m_pPlayer;
      Point m_coordinates;
      unsigned int m_radius;
      double m_countFleet;

      QTime m_timeLastUpdate;
   }; // struct CPlanet

   struct CFleet : public CGameObject
   {
      CPlayer* m_pPlayer;
      CPlanet* m_fromPlanet;
      CPlanet* m_toPlanet;

      QTime m_timeStartMove;
   }; // struct CFleet

} // namespace SingleGame
