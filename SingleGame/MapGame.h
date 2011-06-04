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

      void SetPlayers(const std::vector<CPlayer>& vPlayer);

   private:
      unsigned int m_widthMap;
      unsigned int m_heigthMap;
      unsigned int m_flySpeed;
      unsigned int m_growSpeed;

      std::vector<CPlanet> m_vPlanet;
      std::list<CFleet> m_vFleet;

      static const unsigned int m_cMaxPlanetRadius = 50;
      static const unsigned int m_cMinPlanetRadius = 10;

   }; // class CMapGame

} // namespace SingleGame


