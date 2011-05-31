#include "Space.h"
#include "Planet.h"
#include "Player.h"
#include <vector>

struct CPlanetStartData
{
   int m_planetId;
   int m_planetR;
   int m_planetX;
   int m_planetY;
   int m_playerId;
   int m_countFleet;
};

struct CPlayerStartData
{
   int m_playerId;
   std::string m_playerName;
};

struct CMessageStartMapGame
{

};

CSpace::CSpace(short width, short height, int growth, int speed,
               std::vector<CPlanetStartData> planetList,
               std::vector<CPlayerStartData> playerList):
   m_width(width),
   m_height(height),
   m_growth(growth),
   m_speed(speed)
{
   for (int i = 0; i < planetList.size(); ++i)
   {
      CPlanet* curr_planet = new CPlanet();

   }
}

CSpace::Update(const double i_time)
{
   for(int i = 0; i < m_planets.size(); ++i)
   {
      m_planets[i]->
   }
}
