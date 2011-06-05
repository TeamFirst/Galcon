#include <stdlib.h>

#include "Bot.h"

namespace SingleGame
{
   CBot::CBot()
   {
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
      Message::CMessageStepPlayerPtr ptr(
               new Message::CMessageStepPlayer);

      if(!m_player->m_vPlanet.empty())
      {
         ptr->m_startPlanetID.push_back((*m_player->m_vPlanet.begin())->GetID());
      }

      size_t countPlanet = m_mapGame->GetPlanets().size();
      if(countPlanet)
      {
         ptr->m_finishPlanetID =
            m_mapGame->GetPlanets()[rand() % countPlanet].GetID();
      }

      ptr->m_percent = 1;

      return ptr;
   }

} // namespace SingleGame
