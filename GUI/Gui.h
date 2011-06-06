#pragma once

#include <QObject>
#include "Player.h"
#include "message/MessageConnectToServer.h"
#include "message/MessageTimeToStartGame.h"
#include "message/MessageStartMapGame.h"
#include "message/MessageError.h"
#include "message/MessageAddView.h"
#include "message/MessageFinishGame.h"
#include "message/MessageStepPlayer.h"
#include "message/MessageInformation.h"

namespace GUI
{
   class CPlayWindow;
   class CWaitWindow;
   class CEnterWindow;
   class ISceneUpdates;

   class CGUI : public QObject
   {
      Q_OBJECT
   public:

      explicit CGUI(std::vector<CPlayer* >* players, QObject *parent = 0);
      virtual ~CGUI();

      void ShowWindow();
      void DestroyWindow();

   public slots:
      void TakeConfirmConnectToServer(const Message::CMessageConfirmationConnectToServerPtr mess);

      void TakeError(const Message::CMessageErrorPtr mess);

      void TakeFinishGame(const Message::CMessageFinishGamePtr mess);

      void TakeTimeStartToGame(const Message::CMessageTimeToStartGamePtr mess);

      void TakeFieldSize(const unsigned int X, const unsigned int Y);

      void TakeInInformation(const Message::CMessageInformationPtr mess);

   signals:
      void SendClientToServer(const Message::CMessageConnectToServerPtr mess);
      void SendView(Message::CMessageAddViewPtr mess);
      void SendStepPlayer(const Message::CMessageStepPlayerPtr mess);

   private:
      CWaitWindow* m_waitWindow;
      CEnterWindow* m_enterWindow;
      CPlayWindow* m_playWindow;

      unsigned int m_playerId;
      std::vector<CPlayer* >* m_players;

   }; // class CGUI
} // Namespace GUI

