#include "Galcon.h"

CGalcon::CGalcon()
{
   m_gui = new CGUI();
   m_manager = new ServerManagerDecl::CServerManager();
   m_game = new CGame();
   connectSendersToTakers();
   m_gui->Exec();
}

void CGalcon::connectSendersToTakers()
{
   connect(m_gui, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)), m_manager, SLOT(TakeServerConnect(Message::CMessageConnectToServerPtr)));
   connect(m_game, SIGNAL(SendStartGame(uint,uint)), m_gui, SLOT(TakeFieldSize(uint,uint)));
   connect(m_game, SIGNAL(signalTimer()), m_game, SLOT(slotTimer()));
   connect(m_manager, SIGNAL(SendStartGame(Message::CMessageStartMapGamePtr)),
           m_game, SLOT(SlotStartData(Message::CMessageStartMapGamePtr)));
   connect(m_manager, SIGNAL(SendStateMap(Message::CMessageStateMapPtr)),
           m_game, SLOT(SlotStateMap(Message::CMessageStateMapPtr)));
   connect(m_manager, SIGNAL(SendConfirmConnect(Message::CMessageConfirmationConnectToServerPtr)),
           m_gui, SLOT(TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr)));
   connect(m_manager, SIGNAL(SendTimeToStart(Message::CMessageTimeToStartGamePtr)),
           m_gui, SLOT(TakeStartGame(Message::CMessageTimeToStartGamePtr)));
   //connect(m_manager, SIGNAL(SendFinishGame(Message::CMessageFinishGamePtr)), m_gui, SLOT());
   connect(m_manager, SIGNAL(SendFinishGame(Message::CMessageFinishGamePtr)),
           m_game, SLOT(SlotFinishGame(Message::CMessageFinishGamePtr)));
   connect(m_manager, SIGNAL(SendError(Message::CMessageErrorPtr)),
           m_gui, SLOT(TakeError(Message::CMessageErrorPtr)));
   connect(m_gui, SIGNAL(SendScene(Message::CMessageAddViewPtr)),
           m_game, SLOT(AddView(Message::CMessageAddViewPtr)));
}
