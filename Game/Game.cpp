/// @file Game.cpp
/// @author Dmitriy Kozhevnikov
/// @date 06-06-2011

#include "Game.h"
#include "Space.h"

namespace Game
{
   CGame::CGame(std::vector<CPlayer *> *players) :
      m_players(players)
   {
      m_timer = new QTimer(this);
      connect(m_timer, SIGNAL(timeout()), this, SIGNAL(signalTimer()));
   }

   void CGame::AddView(Message::CMessageAddViewPtr mes)
   {
      m_view = mes->m_view;
      m_view->OnUpdate(m_space->GetPlanets(), m_space->GetFleets());
      m_timer->start(m_timeTick);
   }

   void CGame::DeleteGame()
   {
      m_timer->stop();

      delete m_space;
   }

   void CGame::slotTimer()
   {
      m_space->Update(1.0*(double)m_timeTick/1000);
      m_view->OnUpdate(m_space->GetPlanets(), m_space->GetFleets());
   }

   void CGame::SlotFinishGame(Message::CMessageFinishGamePtr)
   {
      DeleteGame();
   }

   void CGame::SlotStartData(Message::CMessageStartMapGamePtr data)
   {
      bool flagRightData = true;
      QString errorMessage;

      /// Add players
      Message::CPlayerStartData currPlayer;
      foreach (currPlayer, data->m_playerData)
      {
         if (currPlayer.m_playerID >= 1 && currPlayer.m_playerID <= 8)
         {
            CPlayer* player = new CPlayer(currPlayer.m_playerID,
                                          currPlayer.m_playerName);
            m_players->push_back(player);
         }
         else
         {
            flagRightData = false;
            errorMessage = "Failed player " + QString().setNum(currPlayer.m_playerID).toAscii();
         }
      }

      /// Check planets
      Message::CPlanetStartData currPlanet;
      foreach (currPlanet, data->m_planetData)
      {
         if (!AvailiblePlayer(currPlanet.m_playerID) && (currPlanet.m_playerID != 0))
         {
            flagRightData = false;
            errorMessage = "Failed planet owner in planet " +
                  QString().setNum(currPlanet.m_planetID).toAscii() + " has player " +
                  QString().setNum(currPlayer.m_playerID).toAscii();
         }
      }

      m_space = new CSpace(data->m_flyV,
                           data->m_growV,
                           data->m_mapX,
                           data->m_mapY,
                           data->m_planetData);

      if (flagRightData)
      {
         emit SendStartGame(data->m_mapX, data->m_mapY);
      }
      else
      {
         Message::CMessageInformationPtr mess(new Message::CMessageInformation);
         mess->m_typeInformation = Message::CMessageInformation::eGameError;
         mess->m_strInformation = "Wrong start data";
         emit SendError(mess);
      }
   }

   void CGame::SlotStateMap(Message::CMessageStateMapPtr data)
   {
      if (CheckStateData(data))
      {
         m_space->SetPlanets(data->m_planetState);
         m_space->SetFleets(data->m_fleetState);

         m_view->OnUpdate(m_space->GetPlanets(), m_space->GetFleets());
      }
      else
      {
         Message::CMessageInformationPtr mess(new Message::CMessageInformation);
         mess->m_typeInformation = Message::CMessageInformation::eGameError;
         mess->m_strInformation = "Wrong state data";
         emit SendError(mess);
      }
   }

   inline bool CGame::AvailiblePlayer(unsigned int id) const
   {
      CPlayer* currPl;
      foreach (currPl, *m_players)
      {
         if (currPl->GetId() == id)
         {
            return true;
         }
      }
      return false;
   }

   bool CGame::CheckStateData(Message::CMessageStateMapPtr mess) const
   {
      Message::CStatePlanet currPlanet;
      foreach (currPlanet, mess->m_planetState)
      {
         if (!AvailiblePlayer(currPlanet.m_playerID) && (currPlanet.m_playerID != 0))
         {
            return false;
         }
         if (!m_space->CheckPlanetId(currPlanet.m_planetID))
         {
            return false;
         }
      }
      Message::CStateFleet currFleet;
      foreach (currFleet, mess->m_fleetState)
      {
         if (!m_space->CheckPlanetId(currFleet.m_planetStartID) ||
               !m_space->CheckPlanetId(currFleet.m_planetFinishID))
         {
            return false;
         }
      }
      return true;
   }
} // Namespace Game
