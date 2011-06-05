#pragma once

#include <string>
#include <QTime>
#include <math.h>

namespace SingleGame
{
   struct CPlayer;

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
            m_countFleet += ( double(time.toMSecsSinceEpoch() - m_timeLastUpdate.toMSecsSinceEpoch()) / 1000)
                  * v * m_radius;
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

         return m_timeStartMove.addMSecs((distance / v) * 1000);
      }
   }; // struct CFleet

   struct CPlayer : public CGameObject
   {
      void SetNeutral()
      {
         CGameObject::m_ID = 0;
      }

      std::string m_name;

      void AddFleet(CFleet* pFleet)
      {
         m_vFleet.push_back(pFleet);
      }

      void DeleteFleet(const unsigned int ID)
      {
         std::list<CFleet*>::iterator itB = m_vFleet.begin();
         std::list<CFleet*>::iterator itE = m_vFleet.end();
         for(; itB != itE; ++itB)
         {
            if((*itB)->GetID() == ID)
            {
               m_vFleet.erase(itB);
               break;
            }
         }
      }

      void AddPlanet(CPlanet* pPlanet)
      {
         m_vPlanet.push_back(pPlanet);
      }

      void DeletePlanet(const unsigned int ID)
      {
         std::list<CPlanet*>::iterator itB = m_vPlanet.begin();
         std::list<CPlanet*>::iterator itE = m_vPlanet.end();
         for(; itB != itE; ++itB)
         {
            if((*itB)->GetID() == ID)
            {
               m_vPlanet.erase(itB);
               break;
            }
         }
      }

      bool Empty() const ///< return true if player no have fleets or planets
      {
         return m_vPlanet.empty() && m_vFleet.empty();
      }

      std::list<CPlanet*> m_vPlanet;
      std::list<CFleet*> m_vFleet;
   }; // struct CPlayer

} // namespace SingleGame
