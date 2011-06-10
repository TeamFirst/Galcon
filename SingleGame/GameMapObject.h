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
         m_ID = ++sID;
      }

      unsigned int GetID() const
      {
         return m_ID;
      }


      static void ClearID()
      {
         sID = 0;
      }

   protected:

      static unsigned int sID;

      unsigned int m_ID;

   }; // struct CGameObject   

   struct CPlanet : public CGameObject
   {
      CPlayer* m_pPlayer;
      Point m_coordinates;
      unsigned int m_radius;
      double m_countFleet;

      qint64 m_timeLastUpdate;

      void UpdatePlanet(const qint64 time, const unsigned int v)
      {
         if(m_timeLastUpdate < time)
         {
            m_countFleet += ( double(time - m_timeLastUpdate) / 1000)
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

      qint64 m_timeStartMove;
      qint64 m_timeFinishMove;

      void SetTimeFinish(const unsigned int v)
      {
         double distance = sqrt(
            (m_fromPlanet->m_coordinates.x - m_toPlanet->m_coordinates.x)
            * (m_fromPlanet->m_coordinates.x - m_toPlanet->m_coordinates.x)
            + (m_fromPlanet->m_coordinates.y - m_toPlanet->m_coordinates.y)
            * (m_fromPlanet->m_coordinates.y - m_toPlanet->m_coordinates.y));         

         m_timeFinishMove = m_timeStartMove + (distance / v) * 1000;
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
