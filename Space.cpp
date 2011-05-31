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
   double plGrowth = i_time * m_growth;
   double flMove = i_time * m_speed;
   for (unsigned int i = 0; i < m_planets.size(); ++i)
   {
      m_planets[i]->SetArmy(m_planets[i]->GetArmy() + plGrowth);
   }
   for(std::list<CFleet*>::iterator iter = m_fleets.begin(); iter != m_fleets.end(); ++iter)
   {
      iter.operator *()->IncreaseWay(flMove);
   }

}

void CSpace::SetPlanets(const PlanetCont& planets)
{
   int currId(0);
   for (unsigned int i = 0; i != m_planets.size(); ++i)
   {
      if (planets.find(m_planets[i]->GetId()) != planets.end())
      {
         m_planets[i]->SetArmy(planets.find(m_planets[i]->GetId())->second.first);
         m_planets[i]->SetPlayer(planets.find(m_planets[i]->GetId())->second.second);
      }
   }
}

void CSpace::SetFleets(const Message::CStateFleet& message)
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
