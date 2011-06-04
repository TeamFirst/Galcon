#pragma once

#include <vector>
#include <list>

#include "GameMapObject.h"

namespace SingleGame
{
   class CMapGame
   {
   public:
      CMapGame();
      ~CMapGame();

   public:
      void GenerationMap(
         const unsigned int widthMap,
         const unsigned int heigthMap,
         const unsigned int flySpeed,
         const unsigned int growSpeed);

      void SetPlayers(std::vector<CPlayer>& vPlayer);

      const std::vector<CPlanet>& GetPlanets() const;
      const std::list<CFleet>& GetFleets() const;
      const unsigned int GetWidthMap() const;
      const unsigned int GetHeigthMap() const;
      const unsigned int GetFlySpeed() const;
      const unsigned int GetGrowSpeed() const;

   private:
      void createPlanet();

      unsigned int m_widthMap;
      unsigned int m_heigthMap;
      unsigned int m_flySpeed;
      unsigned int m_growSpeed;

      std::vector<CPlanet> m_vPlanet;
      std::list<CFleet> m_vFleet;
      CPlayer m_neutralPlayer;

      static const unsigned int m_cMaxPlanetRadius = 20;
      static const unsigned int m_cMinPlanetRadius = 10;
      static const unsigned int m_cCoefDispersionPlanets = 3;
      static const unsigned int m_cMinFleetCount = 50;
      static const unsigned int m_cMaxFleetCount = 100;

   }; // class CMapGame

} // namespace SingleGame


