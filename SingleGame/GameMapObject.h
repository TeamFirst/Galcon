#pragma once

#include <string>
#include <QTime>
#include <math.h>

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

      QDateTime m_timeLastUpdate;

      void UpdatePlanet(const QDateTime& time, const unsigned int v)
      {
         if(m_timeLastUpdate < time)
         {
            m_countFleet += ( (time.toMSecsSinceEpoch() - m_timeLastUpdate.toMSecsSinceEpoch()) / 1000) * v;
            m_timeLastUpdate = time;
         }
      }
   }; // struct CPlanet

   struct CFleet : public CGameObject
   {
      CPlayer* m_pPlayer;
      CPlanet* m_fromPlanet;
      CPlanet* m_toPlanet;
      unsigned int m_countFleet;

      QDateTime m_timeStartMove;

      QDateTime GetTimeFinish(const unsigned int v) const
      {
         double distance = sqrt(
            (m_fromPlanet->m_coordinates.x - m_toPlanet->m_coordinates.x)
            * (m_fromPlanet->m_coordinates.x - m_toPlanet->m_coordinates.x)
            + (m_fromPlanet->m_coordinates.y - m_toPlanet->m_coordinates.y)
            * (m_fromPlanet->m_coordinates.y - m_toPlanet->m_coordinates.y));

         QDateTime tempTime = m_timeStartMove;
         tempTime.addMSecs((distance / v) * 1000);

         return tempTime;
      }
   }; // struct CFleet

} // namespace SingleGame
