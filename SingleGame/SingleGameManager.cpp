#include <QVariant>

#include "SingleGameManager.h"

namespace SingleGame
{
/// ---------------- constructor
   CSingleGameManager::CSingleGameManager() :
      m_timerWaitStart(this),
      m_timerRunTime(this),
      m_timerBot(this)
   {
      m_timerWaitStart.setInterval(1000);
      m_timerRunTime.setInterval(2000);
      connect(&m_timerWaitStart, SIGNAL(timeout()), this, SLOT(slotWaitTime()));
      connect(&m_timerRunTime, SIGNAL(timeout()), this, SLOT(slotRunTime()));
      connect(&m_timerBot, SIGNAL(timeout()), this, SLOT(slotStepBot()));
   }

   CSingleGameManager::~CSingleGameManager()
   {
   }

/// -------------------------- publoc slots
   void CSingleGameManager::TakeServerConnect(const Message::CMessageConnectToSingleGamePtr pMessage)
   {      
      bool start = startGame(
               0, //< time to start
               pMessage->m_mapWidth,
               pMessage->m_mapHeigth,
               pMessage->m_flySpeed,
               pMessage->m_growSpeed,
               pMessage->m_namePlayer,
               pMessage->m_planetMinSize,
               pMessage->m_planetMaxSize,
               pMessage->m_dispersionPlanets,
               pMessage->m_fleetMinCount,
               pMessage->m_fleetMaxCount,
               pMessage->m_botNumber,
               pMessage->m_botLevel
               );
      if(!start)
      {
         clear();
      }
   }

   void CSingleGameManager::TakeStepPlayer(const Message::CMessageStepPlayerPtr pMessage)
   {
      m_mapGame.UpdateStateMap(
               pMessage->m_finishPlanetID,
               pMessage->m_percent,
               pMessage->m_startPlanetID);

      slotRunTime();
   }

   void CSingleGameManager::slotStepBot()
   {      
      foreach(CBot bot, m_vBot)
      {
         if(bot.HasPlanets())
         {
            TakeStepPlayer(bot.StepBot());
         }
      }
   }

/// ----------------- generation start data
   bool CSingleGameManager::startGame(
      const unsigned int timeToStart,
      const unsigned int widthMap,
      const unsigned int heigthMap,
      const unsigned int flySpeed,
      const unsigned int growSpeed,
      const std::string& namePlayer,
      const unsigned int planetMinSize,
      const unsigned int planetMaxSize,
      const unsigned int dispersionPlanets,
      const unsigned int fleetMinCount,
      const unsigned int fleetMaxCount,
      const unsigned int botNumber,
      const unsigned int botLevel
      )
   {
      /// register player
      CPlayer tempPlayer;
      tempPlayer.m_name = namePlayer;
      tempPlayer.GenerationID();
      m_vPlayer.push_back(tempPlayer);      

      /// bots      
      createBot(botNumber, botLevel);

      /// generation play map
      m_mapGame.GenerationMap(
         widthMap,
         heigthMap,
         flySpeed,
         growSpeed,
         planetMinSize,
         planetMaxSize,
         dispersionPlanets,
         fleetMinCount,
         fleetMaxCount);

      if(m_mapGame.CountPlanets() < m_vPlayer.size())
      {
         return false;
      }

      /// send message with register player
      Message::CMessageConfirmationConnectToServerPtr ptr(
               new Message::CMessageConfirmationConnectToServer);

      ptr->m_playerID = tempPlayer.GetID();
      SendConfirmConnect(ptr);

      /// set planet's owner
      m_mapGame.SetPlayers(m_vPlayer);

      /// start timer Wait
      m_timeToStart = timeToStart;
      if(m_timeToStart)
      {
         slotWaitTime();
         m_timerWaitStart.start();
      }

      if(!m_timeToStart)
      {
         m_timerWaitStart.stop();
         runPlay();
      }

      return true;
   }

   void CSingleGameManager::clear()
   {
      m_vPlayer.clear();
      m_timerWaitStart.stop();
      m_timerRunTime.stop();
      m_timerBot.stop();
      m_timeToStart = 0;
      m_vBot.clear();      

      CGameObject::ClearID();
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
         tempFleet.m_countFleet = itBFleet->m_countFleet;
         tempFleet.m_fleetID = itBFleet->GetID();
         tempFleet.m_percentRoute = 100 *
               (nowTime.toMSecsSinceEpoch()
               - itBFleet->m_timeStartMove.toMSecsSinceEpoch())
               / (itBFleet->GetTimeFinish(m_mapGame.GetFlySpeed()).toMSecsSinceEpoch()
               - itBFleet->m_timeStartMove.toMSecsSinceEpoch());
         tempFleet.m_planetFinishID = itBFleet->m_toPlanet->GetID();
         tempFleet.m_planetStartID = itBFleet->m_fromPlanet->GetID();
         tempFleet.m_playerID = itBFleet->m_pPlayer->GetID();

         ptr->m_fleetState.push_back(tempFleet);
      }

      std::vector<CPlanet>::const_iterator itBPlanet = m_mapGame.GetPlanets().begin();
      std::vector<CPlanet>::const_iterator itEPlanet = m_mapGame.GetPlanets().end();

      Message::CStatePlanet tempPlanet;
      for(; itBPlanet != itEPlanet; ++itBPlanet)
      {
         tempPlanet.m_countFleet = itBPlanet->m_countFleet;         
         tempPlanet.m_planetID = itBPlanet->GetID();         
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

         Message::CMessageFinishGamePtr ptr(
                  new Message::CMessageFinishGame);

         ptr->m_playerID = winnId;

         m_mapGame.Clear();
         clear();

         SendFinishGame(ptr);
      }
   }

/// -------------------------------- bot
   void CSingleGameManager::createBot(
         const unsigned int botNumber,
         const unsigned int botLevel)
   {
      CBot tempBot;
      CPlayer tempPlayer;

      /// register bots
      for(unsigned int i = 0; i < botNumber; ++i)
      {
         tempPlayer.m_name = "Bot" + QVariant(i + 1).toString().toStdString();
         tempPlayer.GenerationID();
         m_vPlayer.push_back(tempPlayer);
      }

      std::vector<CPlayer>::iterator itB = m_vPlayer.begin();
      std::vector<CPlayer>::iterator itE = m_vPlayer.end();      

      for(++itB; itB != itE; ++itB)
      {
         tempBot.CreateBot(&(*itB), &m_mapGame, botLevel);
         m_vBot.push_back(tempBot);
      }

      m_timerBot.setInterval((10 - botLevel + 1) * 1000);
   }

} // namespace SingleGame
