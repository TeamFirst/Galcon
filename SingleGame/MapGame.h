#pragma once

#include <vector>
#include <list>
#include <QTime>

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

      void UpdateStateMap(
         const unsigned int finishPlanetID,
         const unsigned int percent,
         const std::vector<unsigned int>& startPlanetID);
      void UpdateStateMap();

   private:
      void createPlanet();

      void updateFleet();
      void updatePlanet(QDateTime time);

      void addFleet(
         const unsigned int finishPlanetID,
         const unsigned int percent,
         const std::vector<unsigned int>& startPlanetID);

      CPlanet* getPlanet(const unsigned int ID);

      /// find position fleet with time finish more than parametres fleet
      std::list<CFleet>::iterator findInsertFleetPosition(const CFleet& fleet);

      unsigned int m_widthMap;
      unsigned int m_heigthMap;
      unsigned int m_flySpeed;
      unsigned int m_growSpeed;

      std::vector<CPlanet> m_vPlanet;
      std::list<CFleet> m_vFleet; ///< sorted for time finish
      CPlayer m_neutralPlayer;

      static const unsigned int m_cMaxPlanetRadius = 20;
      static const unsigned int m_cMinPlanetRadius = 1;
      static const unsigned int m_cCoefDispersionPlanets = 5;
      static const unsigned int m_cMinFleetCount = 10;
      static const unsigned int m_cMaxFleetCount = 100;

   }; // class CMapGame

} // namespace SingleGame


