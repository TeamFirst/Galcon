#include "SingleGameManager.h"

namespace SingleGame
{
/// ---------------- constructor
   CSingleGameManager::CSingleGameManager()
   {
      m_timerWaitStart.setInterval(1000);
      m_timerRunTime.setInterval(500);
      m_timerBot.setInterval(100000);
      connect(&m_timerWaitStart, SIGNAL(timeout()), this, SLOT(slotWaitTime()));
      connect(&m_timerRunTime, SIGNAL(timeout()), this, SLOT(slotRunTime()));
      connect(&m_timerBot, SIGNAL(timeout()), this, SLOT(slotStepBot()));
   }

   CSingleGameManager::~CSingleGameManager()
   {
   }

/// -------------------------- publoc slots
   void CSingleGameManager::TakeServerConnect(const Message::CMessageConnectToServerPtr pMessage)
   {
      startGame(
               0, //< time to start
               500, //< width map
               400, //< heigth map
               20, //< fly speed
               1, //< grow spped
               pMessage->m_namePlayer,
               2 //< count bots
               );
   }

   void CSingleGameManager::TakeStepPlayer(const Message::CMessageStepPlayerPtr pMessage)
   {
      m_mapGame.UpdateStateMap(
               pMessage->m_finishPlanetID,
               pMessage->m_percent,
               pMessage->m_startPlanetID);
   }

   void CSingleGameManager::slotStepBot()
   {
      std::vector<CBot>::iterator itB = m_vBot.begin();
      std::vector<CBot>::iterator itE = m_vBot.end();

      Message::CMessageStepPlayerPtr ptr(
               new Message::CMessageStepPlayer);

      for(; itB != itE; ++itB)
      {
         ptr = itB->StepBot();
         TakeStepPlayer(ptr);
      }
   }

/// ----------------- generation start data
   void CSingleGameManager::startGame(
      const unsigned int timeToStart,
      const unsigned int widthMap,
      const unsigned int heigthMap,
      const unsigned int flySpeed,
      const unsigned int growSpeed,
      const std::string& namePlayer,
      const unsigned int countBot
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
      if(m_timeToStart)
      {
         slotWaitTime();
         m_timerWaitStart.start();
      }

      /// bots
      createBot(countBot);

      /// generation play map
      m_mapGame.GenerationMap(widthMap, heigthMap, flySpeed, growSpeed);
      m_mapGame.SetPlayers(m_vPlayer);

      if(!m_timeToStart)
      {
         m_timerWaitStart.stop();
         runPlay();
      }
   }

/// --------------------------- timers
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
      //void SendStateMap(const Message::CMessageStateMapPtr pMessage);
      m_mapGame.UpdateStateMap();
      QDateTime nowTime = QDateTime::currentDateTime();

      Message::CMessageStateMapPtr ptr(
               new Message::CMessageStateMap);

      std::list<CFleet>::const_iterator itBFleet = m_mapGame.GetFleets().begin();
      std::list<CFleet>::const_iterator itEFleet = m_mapGame.GetFleets().end();

      Message::CStateFleet tempFleet;
      for(; itBFleet != itEFleet; ++itBFleet)
      {
         CFleet tFleet = *itBFleet;
         //std::vector<CStateFleet> m_fleetState;
         //   unsigned int m_countFleet;
         tempFleet.m_countFleet = itBFleet->m_countFleet;
         //   unsigned int m_fleetID;
         tempFleet.m_fleetID = itBFleet->GetID();
         //   unsigned int m_percentRoute;
         tempFleet.m_percentRoute = 100 *
               (nowTime.toMSecsSinceEpoch()
               - itBFleet->m_timeStartMove.toMSecsSinceEpoch())
               / (itBFleet->GetTimeFinish(m_mapGame.GetFlySpeed()).toMSecsSinceEpoch()
               - itBFleet->m_timeStartMove.toMSecsSinceEpoch());
         //   unsigned int m_planetFinishID;
         tempFleet.m_planetFinishID = itBFleet->m_toPlanet->GetID();
         //   unsigned int m_planetStartID;
         tempFleet.m_planetStartID = itBFleet->m_fromPlanet->GetID();
         //   unsigned int m_playerID;
         tempFleet.m_playerID = itBFleet->m_pPlayer->GetID();

         ptr->m_fleetState.push_back(tempFleet);
      }

      std::vector<CPlanet>::const_iterator itBPlanet = m_mapGame.GetPlanets().begin();
      std::vector<CPlanet>::const_iterator itEPlanet = m_mapGame.GetPlanets().end();

      Message::CStatePlanet tempPlanet;
      for(; itBPlanet != itEPlanet; ++itBPlanet)
      {
         //std::vector<CStatePlanet> m_planetState;
         //   unsigned int m_countFleet;
         tempPlanet.m_countFleet = itBPlanet->m_countFleet;
         //   unsigned int m_planetID;
         tempPlanet.m_planetID = itBPlanet->GetID();
         //   unsigned int m_playerID;
         tempPlanet.m_playerID = itBPlanet->m_pPlayer->GetID();

         ptr->m_planetState.push_back(tempPlanet);
      }

      SendStateMap(ptr);
      checkEndGame();
   }

/// ------------------------- run play
   void CSingleGameManager::runPlay()
   {
      Message::CMessageStartMapGamePtr ptr(
               new Message::CMessageStartMapGame);

      ptr->m_flyV = m_mapGame.GetFlySpeed();
      ptr->m_growV = m_mapGame.GetGrowSpeed();
      ptr->m_mapX = m_mapGame.GetWidthMap();
      ptr->m_mapY = m_mapGame.GetHeigthMap();

      Message::CPlanetStartData tempPlanet;
      std::vector<CPlanet>::const_iterator itB = m_mapGame.GetPlanets().begin();
      std::vector<CPlanet>::const_iterator itE = m_mapGame.GetPlanets().end();
      for(; itB != itE; ++itB)
      {
         tempPlanet.m_countFleet = itB->m_countFleet;
         tempPlanet.m_planetID = itB->GetID();
         tempPlanet.m_planetR = itB->m_radius;
         tempPlanet.m_planetX = itB->m_coordinates.x;
         tempPlanet.m_planetY = itB->m_coordinates.y;
         tempPlanet.m_playerID = itB->m_pPlayer->GetID();

         ptr->m_planetData.push_back(tempPlanet);
      }

      Message::CPlayerStartData tempPlayer;
      std::vector<CPlayer>::const_iterator itBPl = m_vPlayer.begin();
      std::vector<CPlayer>::const_iterator itEPl = m_vPlayer.end();
      for(; itBPl != itEPl; ++itBPl)
      {
         tempPlayer.m_playerID = itBPl->GetID();
         tempPlayer.m_playerName = itBPl->m_name;

         ptr->m_playerData.push_back(tempPlayer);
      }

      m_timerRunTime.start();

      SendStartGame(ptr);

      m_timerBot.start();
   }

   void CSingleGameManager::checkEndGame()
   {
      std::vector<CPlayer>::iterator itB = m_vPlayer.begin();
      std::vector<CPlayer>::iterator itE = m_vPlayer.end();

      unsigned int countPlayers = 0;
      unsigned int winnId = 0;

      for(; itB != itE; ++itB)
      {
         if(!itB->Empty())
         {
            winnId = itB->GetID();
            ++countPlayers;
         }
      }

      if(countPlayers <= 1)
      {
         m_timerBot.stop();
         m_timerRunTime.stop();

         //void SendFinishGame(const Message::CMessageFinishGamePtr pMessage);
         Message::CMessageFinishGamePtr ptr(
                  new Message::CMessageFinishGame);
         //unsigned int m_playerID;

         ptr->m_playerID = winnId;
         SendFinishGame(ptr);
      }
   }

/// -------------------------------- bot
   void CSingleGameManager::createBot(const unsigned int countBot)
   {
      CBot tempBot;
      CPlayer tempPlayer;

      /// register bots
      tempPlayer.m_name = "Bot1";
      tempPlayer.GenerationID();
      m_vPlayer.push_back(tempPlayer);

      /*tempPlayer.m_name = "Bot2";
      tempPlayer.GenerationID();
      m_vPlayer.push_back(tempPlayer);*/

      std::vector<CPlayer>::iterator itB = m_vPlayer.begin();
      std::vector<CPlayer>::iterator itE = m_vPlayer.end();

      for(++itB; itB != itE; ++itB)
      {
         tempBot.CreateBot(&(*itB), &m_mapGame);
         m_vBot.push_back(tempBot);
      }
   }

} // namespace SingleGame
