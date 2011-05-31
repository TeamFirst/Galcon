#ifndef SPACE_H
#define SPACE_H

#include <vector>
#include <list>

class CPlanet;
class CFleet;

struct CPlanetStartData;

struct CPlayerStartData;

struct CMessageStartMapGame;

class CSpace
{
public:
   CSpace(short, short, int, int , std::vector<CPlanetStartData>, std::vector<CPlayerStartData>);
   ~CSpace();

   void UpdatePlanets(const std::vector<std::pair<unsigned long, unsigned int> >&);
   void Update(const double i_time);
   void CreateFleet(CPlanet*, CPlanet*);
   void DeleteFleet(unsigned int i_nId);
private:

   std::vector<CPlanet* > m_planets;
   std::list<CFleet* > m_fleets;
   unsigned short m_width;
   unsigned short m_height;
   unsigned int m_speed;
   unsigned int m_growth;
};

#endif // SPACE_H
