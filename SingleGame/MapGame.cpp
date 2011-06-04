#include <stdlib.h>

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
      unsigned int countPlanetX = m_widthMap / (m_cCoefDispersionPlanets * m_cMaxPlanetRadius) - 1;
      unsigned int countPlanetY = m_heigthMap / (m_cCoefDispersionPlanets * m_cMaxPlanetRadius) - 1;
      unsigned int countPlanet = countPlanetX * countPlanetY;

      CPlanet tempPlanet;

      for(unsigned int i = 0; i < countPlanet; ++i)
      {
         tempPlanet.GenerationID();
         tempPlanet.m_radius = m_cMaxPlanetRadius;
         tempPlanet.m_coordinates.x = m_cMaxPlanetRadius
               * ( m_cCoefDispersionPlanets + (i % countPlanetX) * m_cCoefDispersionPlanets);
         tempPlanet.m_coordinates.y = m_cMaxPlanetRadius
               * ( m_cCoefDispersionPlanets + (i / countPlanetX) * m_cCoefDispersionPlanets) ;
         tempPlanet.m_countFleet = m_cMaxFleetCount;
         tempPlanet.m_pPlayer = &m_neutralPlayer;

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

} // namespace SingleGame

