#include <QMessageBox>
#include "SingleGameManager.h"

namespace SingleGame
{
/// constructor
   CSingleGameManager::CSingleGameManager()
   {
      m_timerWaitStart.setInterval(1000);
      m_timerRunTime.setInterval(500);
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
               0, //< time to start
               1000, //< width map
               500, //< heigth map
               20, //< fly speed
               1, //< grow spped
               pMessage->m_namePlayer);
   }

   void CSingleGameManager::TakeStepPlayer(const Message::CMessageStepPlayerPtr pMessage)
   {
      QMessageBox mBox;
      mBox.setText("take step player");
      mBox.exec();

      m_mapGame.UpdateStateMap(
               pMessage->m_finishPlanetID,
               pMessage->m_percent,
               pMessage->m_startPlanetID);
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
      if(m_timeToStart)
      {
         slotWaitTime();
         m_timerWaitStart.start();
      }

      /// generation play map
      m_mapGame.GenerationMap(widthMap, heigthMap, flySpeed, growSpeed);
      m_mapGame.SetPlayers(m_vPlayer);

      if(!m_timeToStart)
      {
         m_timerWaitStart.stop();
         runPlay();
      }
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
   }

/// run play
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
   }

} // namespace SingleGame
