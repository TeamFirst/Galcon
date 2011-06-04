#pragma once

#include <vector>
#include <list>
#include <map>

#include "message/MessageStartMapGame.h"
#include "message/MessageStateMap.h"

#include "Planet.h"
#include "Fleet.h"

namespace Game
{
   class CSpace
   {
   public:

      CSpace(unsigned short flySpeed, unsigned short growSpeed, unsigned short xSize, unsigned short ySize,
             std::vector<Message::CPlanetStartData> planets);
      ~CSpace();

      //typedef std::map<unsigned short, std::pair<unsigned long, unsigned short> > PlanetCont;

      void SetPlanets(const std::vector<Message::CStatePlanet>&);
      void SetFleets(const std::vector<Message::CStateFleet>&);
      void Update(const double i_time);

      std::vector<CPlanet*> GetPlanets() const;
      std::list<CFleet*> GetFleets() const;

      CPlanet* GetPlanetById(unsigned short id) const;

   private:

      std::vector<CPlanet* > m_planets;
      std::list<CFleet* > m_fleets;
      unsigned short m_speed;
      unsigned short m_growth;
      unsigned short m_width;
      unsigned short m_height;

   };
} // Namespace Game

