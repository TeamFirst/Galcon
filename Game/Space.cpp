#include "Space.h"
//#include "Player.h"

namespace Game
{
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
      double flMove = i_time * (double)m_speed;

      // Make growth on planets
      for (unsigned int i = 0; i < m_planets.size(); ++i)
      {
         if (m_planets[i]->GetPlayerId() != 0) //Exclude growth on neutral planets
         {
            m_planets[i]->SetArmy(m_planets[i]->GetArmy() + plGrowth * m_planets[i]->GetRadius());
         }
      }

      // Move fleets
      CFleet* currFleet;
      bool ReachedFleetsPresent(true);
      foreach (currFleet, m_fleets)
      {
         currFleet->IncreaseWay(flMove);
      }

      //Delete reached fleets
      while (ReachedFleetsPresent)
      {
         std::list<CFleet*>::iterator iter;
         for(iter = m_fleets.begin(); iter != m_fleets.end(); ++iter)
         {
            if (iter.operator *()->ReachedDestination())
            {
               break;
            }
         }
         if (iter != m_fleets.end())
         {
            CFleet* toDelete = iter.operator *();
            m_fleets.erase(iter);
            delete toDelete;
         }
         else
         {
            ReachedFleetsPresent = false;
         }
      }

   }

   void CSpace::SetPlanets(const std::vector<Message::CStatePlanet>& i_planets)
   {
      // For every existing planet update its army & owner from given data
      Message::CStatePlanet inPl;
      CPlanet* currPl;
      bool NewFlag = false;
      foreach (inPl, i_planets)
      {
         foreach (currPl, m_planets)
         {
            if (inPl.m_planetID == currPl->GetId())
            {
               NewFlag = true;
               break;
            }
         }
         if (NewFlag)
         {
            currPl->SetArmy(inPl.m_countFleet);
            currPl->SetPlayer(inPl.m_playerID);
         }
      }
   }

   void CSpace::SetFleets(const std::vector<Message::CStateFleet>& message)
   {
      // For every given fleet
      Message::CStateFleet currMessFleet;
      foreach (currMessFleet, message)
      {
         CFleet* currFleet;
         bool flag = true;

         // Search for it in existing list
         foreach (currFleet, m_fleets)
         {
            if (currFleet->GetId() == currMessFleet.m_fleetID)
            {
               currFleet->SetPercent(currMessFleet.m_percentRoute);
               flag = false;
            }
         }

         // If didn't found - add it to list
         if (flag)
         {
            CPlanet* planetFr = GetPlanetById(currMessFleet.m_planetStartID);
            CPlanet* planetTo = GetPlanetById(currMessFleet.m_planetFinishID);
            CFleet* newFleet = new CFleet(currMessFleet.m_fleetID,
                                    planetFr,
                                    planetTo,
                                    currMessFleet.m_playerID,
                                    currMessFleet.m_countFleet,
                                    currMessFleet.m_percentRoute);
            m_fleets.push_front(newFleet);
         }
      }
   }

   std::list<CFleet*> CSpace::GetFleets() const
   {
      return m_fleets;
   }

   std::vector<CPlanet*> CSpace::GetPlanets() const
   {
      return m_planets;
   }

   CPlanet* CSpace::GetPlanetById(unsigned short id) const
   {
      CPlanet* planet;
      foreach (planet, m_planets)
      {
         if (planet->GetId() == id)
            return planet;
      }
      return 0;
   }
} //Namespace Game
