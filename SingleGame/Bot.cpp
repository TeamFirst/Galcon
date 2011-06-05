#include <stdlib.h>

#include "Bot.h"

namespace SingleGame
{
   CBot::CBot()
   {
      //connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotStepPlayer()));
   }

   CBot::~CBot()
   {
   }

   void CBot::CreateBot(CPlayer* botPlayer, CMapGame* mapGame)
   {
      m_player = botPlayer;
      m_mapGame = mapGame;
   }

   const Message::CMessageStepPlayerPtr CBot::StepBot()
   {
      //void SendStepPlayer(const Message::CMessageStepPlayerPtr pMessage);
      /*
      unsigned int m_finishPlanetID;
      unsigned int m_percent;
      std::vector<unsigned int> m_startPlanetID;
      */
      Message::CMessageStepPlayerPtr ptr(
               new Message::CMessageStepPlayer);

      if(!m_player->m_vPlanet.empty())
      {
         ptr->m_startPlanetID.push_back((*m_player->m_vPlanet.begin())->GetID());
      }

      //std::vector<CPlanet>
      size_t countPlanet = m_mapGame->GetPlanets().size();
      if(countPlanet)
      {
         ptr->m_finishPlanetID =
            m_mapGame->GetPlanets()[rand() % countPlanet].GetID();
      }

      ptr->m_percent = 50;

      return ptr;
   }

} // namespace SingleGame
