#pragma once

#include <QObject>
#include <string>

#include "message/MessageConnectToServer.h"
#include "message/MessageTimeToStartGame.h"
#include "message/MessageStartMapGame.h"
#include "message/MessageError.h"
#include "message/MessageAddView.h"
#include "message/MessageFinishGame.h"
#include "message/MessageStepPlayer.h"

class CPlayWindow;
class CWaitWindow;
class CEnterWindow;
class ISceneUpdates;

class CGUI : public QObject
{
   Q_OBJECT
public:

   explicit CGUI(QObject *parent = 0);
   virtual ~CGUI();

   void ShowWindow();
   void HideWindow();

public slots:
   void TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr mess);
   void TakeError(Message::CMessageErrorPtr mess);
   void TakeFinishGame(Message::CMessageFinishGamePtr mess);
   void TakeStartGame(Message::CMessageTimeToStartGamePtr mess);
   void TakeTimeStartToGame(Message::CMessageTimeToStartGamePtr mess);

   void TakeFieldSize(unsigned int X, unsigned int Y);

   void TakeInError(std::string mess);

signals:
   void SendClientToServer(Message::CMessageConnectToServerPtr mess);
   void SendView(Message::CMessageAddViewPtr mess);
   void SendStepPlayer(Message::CMessageStepPlayerPtr mess);

private:
   CWaitWindow * m_waitWindow;
   CEnterWindow * m_enterWindow;
   CPlayWindow * m_playWindow;

   unsigned int m_playerId;

}; // class CGUI


