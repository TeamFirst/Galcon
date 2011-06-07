#include "Galcon.h"

CGalcon::CGalcon()
{
   m_gui = new GUI::CGUI(&m_players);
   m_manager = new ServerManagerDecl::CServerManager();
   m_game = new Game::CGame(&m_players);
   m_singleGame = new SingleGame::CSingleGameManager();
   connectSendersToTakers();
   m_gui->ShowWindow();
}

void CGalcon::connectSendersToTakers()
{
   connect(m_gui, SIGNAL(SendView(Message::CMessageAddViewPtr)),
           m_game, SLOT(AddView(Message::CMessageAddViewPtr)));

   connect(m_game, SIGNAL(SendStartGame(uint,uint)),
           m_gui, SLOT(TakeFieldSize(uint,uint)));
   connect(m_game, SIGNAL(signalTimer()),
           m_game, SLOT(slotTimer()));

   connect(m_gui, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
           m_manager, SLOT(TakeServerConnect(Message::CMessageConnectToServerPtr)));
   connect(m_gui, SIGNAL(SendClientToSingleGame(Message::CMessageConnectToSingleGamePtr)),
           m_singleGame, SLOT(TakeServerConnect(Message::CMessageConnectToSingleGamePtr)));

   connect(m_gui, SIGNAL(signalChoiceNetworkGame()), this, SLOT(slotChoiceNetworkGame()));
   connect(m_gui, SIGNAL(signalChoiceSingleGame()), this, SLOT(slotChoiceSingleGame()));

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

   connect(m_singleGame, SIGNAL(SendConfirmConnect(Message::CMessageConfirmationConnectToServerPtr)),
           m_gui, SLOT(TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr)));
   connect(m_singleGame, SIGNAL(SendError(Message::CMessageErrorPtr)),
           m_gui, SLOT(TakeError(Message::CMessageErrorPtr)));
   connect(m_singleGame, SIGNAL(SendFinishGame(Message::CMessageFinishGamePtr)),
           m_game, SLOT(SlotFinishGame(Message::CMessageFinishGamePtr)));
   connect(m_singleGame, SIGNAL(SendFinishGame(Message::CMessageFinishGamePtr)),
           m_gui, SLOT(TakeFinishGame(Message::CMessageFinishGamePtr)));
   connect(m_singleGame, SIGNAL(SendStateMap(Message::CMessageStateMapPtr)),
           m_game, SLOT(SlotStateMap(Message::CMessageStateMapPtr)));
   connect(m_singleGame, SIGNAL(SendStartGame(Message::CMessageStartMapGamePtr)),
           m_game, SLOT(SlotStartData(Message::CMessageStartMapGamePtr)));
   connect(m_singleGame, SIGNAL(SendTimeToStart(Message::CMessageTimeToStartGamePtr)),
           m_gui, SLOT(TakeTimeStartToGame(Message::CMessageTimeToStartGamePtr)));
   connect(m_singleGame, SIGNAL(SendInInformation(Message::CMessageInformationPtr)),
           m_gui, SLOT(TakeInInformation(Message::CMessageInformationPtr)));


}

void CGalcon::connectNetworkSendersToTakers()
{   
   connect(m_gui, SIGNAL(SendStepPlayer(Message::CMessageStepPlayerPtr)),
           m_manager, SLOT(TakeStepPlayer(Message::CMessageStepPlayerPtr)));
}

void CGalcon::connectSingleSendersToTakers()
{
   connect(m_gui, SIGNAL(SendStepPlayer(Message::CMessageStepPlayerPtr)),
           m_singleGame, SLOT(TakeStepPlayer(Message::CMessageStepPlayerPtr)));
}

/// private slots

void CGalcon::slotChoiceNetworkGame()
{
   connectNetworkSendersToTakers();
}

void CGalcon::slotChoiceSingleGame()
{
   connectSingleSendersToTakers();
}
