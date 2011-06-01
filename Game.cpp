#include "Game.h"

CGame::CGame()
{

}

void CGame::AddView(Message::CMessageAddViewPtr mes)
{
   m_view = mes->m_view;
}

void CGame::DeleteGame()
{
   //stop timer;

   delete m_space;
}

void CGame::slotTimer()
{
   m_space->Update(1.0/(double)m_timeTick);

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
   emit SendStartGame();
}

void CGame::SlotStateMap(Message::CMessageStateMapPtr data)
{

}
