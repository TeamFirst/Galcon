#include "Galcon.h"

CGalcon::CGalcon()
{
   m_gui = new CGUI();
   m_manager = new ServerManagerDecl::CServerManager();
   m_game = new Game::CGame();
   m_singleGame = new SingleGame::CSingleGameManager();
   connectSendersToTakers();
   m_gui->ShowWindow();
}

void CGalcon::connectSendersToTakers()
{
   bool typeGame; // true - network, false - local

   typeGame = true;

   if(typeGame)
   {
      connect(m_manager, SIGNAL(SendConfirmConnect(Message::CMessageConfirmationConnectToServerPtr)),
              m_gui, SLOT(TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr)));
      connect(m_manager, SIGNAL(SendError(Message::CMessageErrorPtr)),
              m_gui, SLOT(TakeError(Message::CMessageErrorPtr)));
      connect(m_manager, SIGNAL(SendFinishGame(Message::CMessageFinishGamePtr)),
              m_game, SLOT(SlotFinishGame(Message::CMessageFinishGamePtr)));
      connect(m_manager, SIGNAL(SendStateMap(Message::CMessageStateMapPtr)),
              m_game, SLOT(SlotStateMap(Message::CMessageStateMapPtr)));
      connect(m_manager, SIGNAL(SendStartGame(Message::CMessageStartMapGamePtr)),
              m_game, SLOT(SlotStartData(Message::CMessageStartMapGamePtr)));
      connect(m_manager, SIGNAL(SendTimeToStart(Message::CMessageTimeToStartGamePtr)),
              m_gui, SLOT(TakeTimeStartToGame(Message::CMessageTimeToStartGamePtr)));
      connect(m_manager, SIGNAL(SendInInformation(Message::CMessageInformationPtr)),
              m_gui, SLOT(TakeInInformation(Message::CMessageInformationPtr)));
   }
   else
   {
      connect(m_singleGame, SIGNAL(SendConfirmConnect(Message::CMessageConfirmationConnectToServerPtr)),
              m_gui, SLOT(TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr)));
      connect(m_singleGame, SIGNAL(SendError(Message::CMessageErrorPtr)),
              m_gui, SLOT(TakeError(Message::CMessageErrorPtr)));
      connect(m_singleGame, SIGNAL(SendFinishGame(Message::CMessageFinishGamePtr)),
              m_game, SLOT(SlotFinishGame(Message::CMessageFinishGamePtr)));
      connect(m_singleGame, SIGNAL(SendStateMap(Message::CMessageStateMapPtr)),
              m_game, SLOT(SlotStateMap(Message::CMessageStateMapPtr)));
      connect(m_singleGame, SIGNAL(SendStartGame(Message::CMessageStartMapGamePtr)),
              m_game, SLOT(SlotStartData(Message::CMessageStartMapGamePtr)));
      connect(m_singleGame, SIGNAL(SendTimeToStart(Message::CMessageTimeToStartGamePtr)),
              m_gui, SLOT(TakeTimeStartToGame(Message::CMessageTimeToStartGamePtr)));
      connect(m_singleGame, SIGNAL(SendInInformation(Message::CMessageInformationPtr)),
              m_gui, SLOT(TakeInInformation(Message::CMessageInformationPtr)));
   }


   connect(m_gui, SIGNAL(SendView(Message::CMessageAddViewPtr)),
           m_game, SLOT(AddView(Message::CMessageAddViewPtr)));

   if(typeGame)
   {
      connect(m_gui, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
              m_manager, SLOT(TakeServerConnect(Message::CMessageConnectToServerPtr)));
      connect(m_gui, SIGNAL(SendStepPlayer(Message::CMessageStepPlayerPtr)),
              m_manager, SLOT(TakeStepPlayer(Message::CMessageStepPlayerPtr)));
   }
   else
   {
      connect(m_gui, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
              m_singleGame, SLOT(TakeServerConnect(Message::CMessageConnectToServerPtr)));
      connect(m_gui, SIGNAL(SendStepPlayer(Message::CMessageStepPlayerPtr)),
              m_singleGame, SLOT(TakeStepPlayer(Message::CMessageStepPlayerPtr)));
   }


   connect(m_game, SIGNAL(SendStartGame(uint,uint)),
           m_gui, SLOT(TakeFieldSize(uint,uint)));
   connect(m_game, SIGNAL(signalTimer()),
           m_game, SLOT(slotTimer()));

}
