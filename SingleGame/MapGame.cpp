#include <stdlib.h>
#include <algorithm>

#include "MapGame.h"

namespace SingleGame
{

   CMapGame::CMapGame()
   {
      m_neutralPlayer.SetNeutral();
   }

   CMapGame::~CMapGame()
   {
   }

/// generation start data
   void CMapGame::GenerationMap(
      const unsigned int widthMap,
      const unsigned int heigthMap,
      const unsigned int flySpeed,
      const unsigned int growSpeed)
   {
      m_widthMap = widthMap;
      m_heigthMap = heigthMap;
      m_flySpeed = flySpeed;
      m_growSpeed = growSpeed;

      createPlanet();
   }

   void CMapGame::createPlanet()
   {
      unsigned int countPlanetX = m_widthMap
            / (m_cCoefDispersionPlanets * m_cMaxPlanetRadius) - 1;
      unsigned int countPlanetY = m_heigthMap
            / (m_cCoefDispersionPlanets * m_cMaxPlanetRadius) - 1;
      unsigned int countPlanet = countPlanetX * countPlanetY;

      CPlanet tempPlanet;

      for(unsigned int i = 0; i < countPlanet; ++i)
      {
         tempPlanet.GenerationID();
         tempPlanet.m_radius = m_cMaxPlanetRadius;
         tempPlanet.m_coordinates.x = m_cMaxPlanetRadius
               * m_cCoefDispersionPlanets
               * (1 + (i % countPlanetX));
         tempPlanet.m_coordinates.y = m_cMaxPlanetRadius
               *  m_cCoefDispersionPlanets
               * (1 + (i / countPlanetX));
         tempPlanet.m_countFleet = m_cMaxFleetCount;
         tempPlanet.m_pPlayer = &m_neutralPlayer;
         tempPlanet.m_timeLastUpdate = QDateTime::currentDateTime();

         m_vPlanet.push_back(tempPlanet);
      }
   }

   void CMapGame::SetPlayers(std::vector<CPlayer>& vPlayer)
   {
      std::vector<CPlayer>::iterator itB = vPlayer.begin();

      for(; itB != vPlayer.end(); ++itB)
      {
         m_vPlanet[rand() % m_vPlanet.size()].m_pPlayer = &(*itB);
      }
   }

/// get data
   const std::vector<CPlanet>& CMapGame::GetPlanets() const
   {
      return m_vPlanet;
   }

   const std::list<CFleet>& CMapGame::GetFleets() const
   {
      return m_vFleet;
   }

   const unsigned int CMapGame::GetWidthMap() const
   {
      return m_widthMap;
   }

   const unsigned int CMapGame::GetHeigthMap() const
   {
      return m_heigthMap;
   }

   const unsigned int CMapGame::GetFlySpeed() const
   {
      return m_flySpeed;
   }

   const unsigned int CMapGame::GetGrowSpeed() const
   {
      return m_growSpeed;
   }

/// update data
   void CMapGame::UpdateStateMap()
   {
      updateFleet();
      updatePlanet(QDateTime::currentDateTime());
   }

   void CMapGame::UpdateStateMap(
      const unsigned int finishPlanetID,
      const unsigned int percent,
      const std::vector<unsigned int>& startPlanetID)
   {
      UpdateStateMap();
      addFleet(finishPlanetID, percent, startPlanetID);
   }

   void CMapGame::updateFleet()
   {
   }

   void CMapGame::updatePlanet(QDateTime time)
   {
      std::vector<CPlanet>::iterator itB = m_vPlanet.begin();
      std::vector<CPlanet>::iterator itE = m_vPlanet.end();
      for(; itB != itE; ++itB)
      {
         if(itB->GetID())
         {
            itB->UpdatePlanet(time, m_growSpeed);
         }
      }
   }

   void CMapGame::addFleet(
      const unsigned int finishPlanetID,
      const unsigned int percent,
      const std::vector<unsigned int>& startPlanetID)
   {
      CFleet tempFleet;

      std::vector<unsigned int>::const_iterator itB = startPlanetID.begin();
      std::vector<unsigned int>::const_iterator itE = startPlanetID.end();

      CPlanet* finishPlanet = getPlanet(finishPlanetID);

      for(; itB != itE; ++itB)
      {
         tempFleet.m_fromPlanet = getPlanet(*itB);
         tempFleet.m_countFleet = getPlanet(*itB)->m_countFleet * percent / 100;
         tempFleet.m_fromPlanet->m_countFleet -= tempFleet.m_countFleet;
         tempFleet.m_toPlanet = finishPlanet;
         tempFleet.GetID();
         tempFleet.m_timeStartMove = QDateTime::currentDateTime();

         m_vFleet.push_back(tempFleet);
      }
   }

   CPlanet* CMapGame::getPlanet(const unsigned int ID)
   {
      std::vector<CPlanet>::iterator itB = m_vPlanet.begin();
      std::vector<CPlanet>::iterator itE = m_vPlanet.end();

      for(; itB != itE; ++itB)
      {
         if(itB->GetID() == ID)
         {
            return &(*itB);
         }
      }

      return &(*itE); /// if this case - error program
   }

} // namespace SingleGame

