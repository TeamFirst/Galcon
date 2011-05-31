#include "Space.h"
#include "Fleet.h"
#include "Planet.h"
#include "Player.h"
#include <vector>


CSpace::CSpace(unsigned short flySpeed, unsigned short growSpeed, unsigned short xSize, unsigned short ySize,
               std::vector<Message::CPlanetStartData> planets):
   m_speed(flySpeed),
   m_growth(growSpeed),
   m_width(xSize),
   m_height(ySize)
{
   for (unsigned int i = 0; i < planets.size(); ++i)
   {
      CPlanet* tempPlanet = new CPlanet(planets[i].m_planetID,
                                        planets[i].m_planetX,
                                        planets[i].m_planetY,
                                        planets[i].m_planetR,
                                        planets[i].m_countFleet,
                                        planets[i].m_playerID);
      m_planets.push_back(tempPlanet);
   }
}

CSpace::~CSpace()
{
   while (!m_fleets.empty())
   {
      CFleet* fl = m_fleets.back();
      m_fleets.pop_back();
      delete fl;
   }

   while (!m_planets.empty())
   {
      CPlanet* pl = m_planets.back();
      m_planets.pop_back();
      delete pl;
   }
}

void CSpace::Update(const double i_time)
{
   for (unsigned int i = 0; i < m_planets.size(); ++i)
   {

   }
}

void CSpace::SetFleet(const Message::CStateFleet &)
{

}

std::list<CFleet*> CSpace::GetFleets() const
{
   return m_fleets;
}

std::vector<CPlanet*> CSpace::GetPlanets() const
{
   return m_planets;
}
