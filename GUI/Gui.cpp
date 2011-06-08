#include <QDialog>
#include <QVariant>

#include "Gui.h"
#include "Mainwindow.h"
#include "Playwindow.h"
#include "Waitwindow.h"
#include "Enterwindow.h"
#include "Singlewindow.h"
#include "Errorwindow.h"

namespace GUI
{
   CGUI::CGUI(std::vector<CPlayer *> *players, QObject *parent) :
      QObject(parent),
      m_playerId(0),
      m_players(players)
   {
      m_mainWindow = new CMainWindow();
      m_enterWindow = new CEnterWindow();
      m_waitWindow = new CWaitWindow();
      m_playWindow = new CPlayWindow();
      m_singleWindow = new CSingleWindow();

      connect(m_enterWindow, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
              this, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)));
      connect(m_singleWindow, SIGNAL(SendClientToSingleGame(Message::CMessageConnectToSingleGamePtr)),
              this, SIGNAL(SendClientToSingleGame(Message::CMessageConnectToSingleGamePtr)));

      connect(m_playWindow, SIGNAL(SendStepPlayer(Message::CMessageStepPlayerPtr)),
              this, SIGNAL(SendStepPlayer(Message::CMessageStepPlayerPtr)));

      connect(m_mainWindow, SIGNAL(signalChoiceSingleGame()),
              this, SLOT(slotChoiceSingleGame()));
      connect(m_mainWindow, SIGNAL(signalChoiceNetworkGame()),
              this, SLOT(slotChoiceNetworkGame()));
   }

   CGUI::~CGUI()
   {
      delete m_mainWindow;
      delete m_enterWindow;
      delete m_waitWindow;
      delete m_playWindow;
      delete m_singleWindow;
   }

   void CGUI::ShowWindow()
   {
      m_mainWindow->ShowWindow();
   }

   void CGUI::DestroyWindow()
   {
      m_mainWindow->DestroyWindow();
   }

   void CGUI::TakeConfirmConnectToServer(const Message::CMessageConfirmationConnectToServerPtr mess)
   {
       m_playerId = mess->m_playerID;
       m_playWindow->SetPlayerId(m_playerId);
       switch(m_typeGame)
       {
       case eSingleGame:
          m_singleWindow->DestroyWindow();
          break;
       case eNetworkGame:
          m_enterWindow->DestroyWindow();
          break;
       }

       m_waitWindow->ShowWindow();
   }

   void CGUI::TakeError(const Message::CMessageErrorPtr mess)
   {
      CErrorWindow::Show("Server error", mess->m_strError.c_str());
      m_playWindow->DestroyWindow();
      m_waitWindow->DestroyWindow();
      m_enterWindow->ShowWindow();
   }

   void CGUI::TakeTimeStartToGame(const Message::CMessageTimeToStartGamePtr mess)
   {
      m_waitWindow->SetSecToStart(mess->m_second);
   }

   void CGUI::TakeFinishGame(const Message::CMessageFinishGamePtr mess)
   {
      m_playWindow->DestroyWindow();
      CPlayer* currPlayer = NULL;
      foreach (currPlayer, *m_players)
      {
         if (mess->m_playerID == currPlayer->GetId())
         {
            break;
         }
      }

      CErrorWindow::Show("Winner!", "Wins "+
         QString::fromStdString(currPlayer->GetName()));

      m_mainWindow->ShowWindow();
      signalDisconnect();
   }

   void CGUI::TakeInInformation(const Message::CMessageInformationPtr)
   {
      //CCriticalMessage::Show("Inside program error", mess->m_strInformation.c_str());
   }

   void CGUI::TakeFieldSize(const unsigned int X, const unsigned int Y)
   {
      m_playWindow->CreateWindow(X, Y);
      m_waitWindow->DestroyWindow();
      m_playWindow->ShowWindow();

      Message::CMessageAddViewPtr ptr(new Message::CMessageAddView);
      ptr->m_view = (GUI::ISceneUpdates*)m_playWindow->GetView();
      SendView(ptr);
   }

   void CGUI::slotChoiceSingleGame()
   {
      m_typeGame = eSingleGame;

      emit signalChoiceSingleGame();

      m_mainWindow->DestroyWindow();
      m_singleWindow->ShowWindow();
   }

   void CGUI::slotChoiceNetworkGame()
   {
      m_typeGame = eNetworkGame;

      emit signalChoiceNetworkGame();

      m_mainWindow->DestroyWindow();
      m_enterWindow->ShowWindow();
   }

} // Namespace GUI
