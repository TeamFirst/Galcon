#include "Galcon.h"

CGalcon::CGalcon()
{
   m_gui = new CGUI();
   m_manager = new ServerManagerDecl::CServerManager();
   m_game = new CGame();
}

void CGalcon::connectSendersToTakers()
{
   connect(m_gui, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)), m_manager, SLOT(TakeServerConnect(Message::CMessageConnectToServerPtr)));

}
