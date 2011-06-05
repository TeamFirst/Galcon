#include "Game.h"

namespace Game
{
   CGame::CGame()
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
      m_space = new CSpace(data->m_flyV,
                           data->m_growV,
                           data->m_mapX,
                           data->m_mapY,
                           data->m_planetData);
      emit SendStartGame(data->m_mapX, data->m_mapY);
   }

   void CGame::SlotStateMap(Message::CMessageStateMapPtr data)
   {
      m_space->SetPlanets(data->m_planetState);
      m_space->SetFleets(data->m_fleetState);


      m_view->OnUpdate(m_space->GetPlanets(), m_space->GetFleets());
   }
} // Namespace Game
