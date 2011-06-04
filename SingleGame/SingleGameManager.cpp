#include "SingleGameManager.h"

namespace SingleGame
{
/// constructor
   CSingleGameManager::CSingleGameManager()
   {
      m_timerWaitStart.setInterval(1000);
      m_timerRunTime.setInterval(2000);
      connect(&m_timerWaitStart, SIGNAL(timeout()), this, SLOT(slotWaitTime()));
      connect(&m_timerRunTime, SIGNAL(timeout()), this, SLOT(slotRunTime()));
   }

   CSingleGameManager::~CSingleGameManager()
   {
   }

/// publoc slots
   void CSingleGameManager::TakeServerConnect(const Message::CMessageConnectToServerPtr pMessage)
   {
      startGame(
               2, //< time to start
               500, //< width map
               500, //< heigth map
               1, //< fly speed
               1, //< grow spped
               pMessage->m_namePlayer);
   }

   void CSingleGameManager::TakeStepPlayer(const Message::CMessageStepPlayerPtr pMessage)
   {
   }

/// generation start data
   void CSingleGameManager::startGame(
      const unsigned int timeToStart,
      const unsigned int widthMap,
      const unsigned int heigthMap,
      const unsigned int flySpeed,
      const unsigned int growSpeed,
      const std::string& namePlayer
      )
   {
      /// register player
      CPlayer tempPlayer;
      tempPlayer.m_name = namePlayer;
      tempPlayer.GenerationID();
      m_vPlayer.push_back(tempPlayer);

      /// send message with register player
      Message::CMessageConfirmationConnectToServerPtr ptr(
               new Message::CMessageConfirmationConnectToServer);

      ptr->m_playerID = tempPlayer.GetID();
      SendConfirmConnect(ptr);

      /// start timer Wait
      m_timeToStart = timeToStart;
      slotWaitTime();
      m_timerWaitStart.start();

      /// generation play map
      m_mapGame.GenerationMap(widthMap, heigthMap, flySpeed, growSpeed);
      m_mapGame.SetPlayers(m_vPlayer);
   }

/// timers
   void CSingleGameManager::slotWaitTime()
   {
      //void SendTimeToStart(const Message::CMessageTimeToStartGamePtr pMessage);
      Message::CMessageTimeToStartGamePtr ptr(
               new Message::CMessageTimeToStartGame);

      ptr->m_second = m_timeToStart;
      SendTimeToStart(ptr);

      --m_timeToStart;

      if(!m_timeToStart)
      {
         m_timerWaitStart.stop();
         runPlay();
      }
   }

   void CSingleGameManager::slotRunTime()
   {
   }

/// run play
   void CSingleGameManager::runPlay()
   {
      //void SendStartGame(const Message::CMessageStartMapGamePtr pMessage);
      Message::CMessageStartMapGamePtr ptr(
               new Message::CMessageStartMapGame);

      //unsigned int m_flyV;
      ptr->m_flyV = m_mapGame.GetFlySpeed();
      //unsigned int m_growV;
      ptr->m_growV = m_mapGame.GetGrowSpeed();
      //unsigned int m_mapX;
      ptr->m_mapX = m_mapGame.GetWidthMap();
      //unsigned int m_mapY;
      ptr->m_mapY = m_mapGame.GetHeigthMap();
      //std::vector<CPlanetStartData> m_planetData;
      Message::CPlanetStartData tempPlanet;
      std::vector<CPlanet>::const_iterator itB = m_mapGame.GetPlanets().begin();
      std::vector<CPlanet>::const_iterator itE = m_mapGame.GetPlanets().end();
      for(; itB != itE; ++itB)
      {
         //   unsigned int m_countFleet;
         tempPlanet.m_countFleet = itB->m_countFleet;
         //   unsigned int m_planetID;
         tempPlanet.m_planetID = itB->GetID();
         //   unsigned int m_planetR;
         tempPlanet.m_planetR = itB->m_radius;
         //   unsigned int m_planetX;
         tempPlanet.m_planetX = itB->m_coordinates.x;
         //   unsigned int m_planetY;
         tempPlanet.m_planetY = itB->m_coordinates.y;
         //   unsigned int m_playerID;
         tempPlanet.m_playerID = itB->m_pPlayer->GetID();

         ptr->m_planetData.push_back(tempPlanet);
      }

      //std::vector<CPlayerStartData> m_playerData;
      Message::CPlayerStartData tempPlayer;
      std::vector<CPlayer>::const_iterator itBPl = m_vPlayer.begin();
      std::vector<CPlayer>::const_iterator itEPl = m_vPlayer.end();
      for(; itBPl != itEPl; ++itBPl)
      {
         //   unsigned int m_playerID;
         tempPlayer.m_playerID = itBPl->GetID();
         //   std::string m_playerName;
         tempPlayer.m_playerName = itBPl->m_name;

         ptr->m_playerData.push_back(tempPlayer);
      }

      SendStartGame(ptr);

   }

} // namespace SingleGame
