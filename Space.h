#ifndef SPACE_H
#define SPACE_H

#include <vector>
#include <list>
#include <map>

#include "message/MessageStartMapGame.h"
#include "message/MessageStateMap.h"

class CPlanet;
class CFleet;

//struct CPlanetStartData;

//struct CPlayerStartData;

//struct CMessageStartMapGame;

class CSpace
{
public:
   CSpace(unsigned short flySpeed, unsigned short growSpeed, unsigned short xSize, unsigned short ySize,
          std::vector<Message::CPlanetStartData> planets);
   ~CSpace();

   typedef std::map<unsigned short, std::pair<unsigned long, unsigned short> > PlanetCont;

   void SetPlanets(const PlanetCont&);
   void SetFleets(const Message::CStateFleet&);
   void Update(const double i_time);

   std::vector<CPlanet*> GetPlanets() const;
   std::list<CFleet*> GetFleets() const;
private:

   std::vector<CPlanet* > m_planets;
   std::list<CFleet* > m_fleets;
   unsigned short m_speed;
   unsigned short m_growth;
   unsigned short m_width;
   unsigned short m_height;

};

#endif // SPACE_H
