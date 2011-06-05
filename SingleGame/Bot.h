#pragma once

#include "SingleGame/GameMapObject.h"
#include "message/MessageStepPlayer.h"
#include "MapGame.h"

namespace SingleGame
{

   class CBot
   {

   public:
      CBot();
      ~CBot();

      void CreateBot(CPlayer* botPlayer, CMapGame* mapGame);      

      const Message::CMessageStepPlayerPtr StepBot();

   private:

      CPlayer* m_player;
      CMapGame* m_mapGame;

   }; // class CBot

} // namespace SingleGame
