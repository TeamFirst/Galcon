#pragma once

#include <QObject>
#include <string>
#include <vector>

#include "message/MessageItf.h"
#include "message/MessageConnectToServer.h"
#include "message/MessageStepPlayer.h"
#include "message/MessageError.h"
#include "message/MessageFinishGame.h"
#include "message/MessageStateMap.h"
#include "message/MessageStartMapGame.h"
#include "message/MessageTimeToStartGame.h"
#include "message/MessageInformation.h"
#include "MapGame.h"


namespace SingleGame
{
   class CSingleGameManager : public QObject
   {
      Q_OBJECT

   public:
       CSingleGameManager();
       ~CSingleGameManager();

   public slots:
      void TakeServerConnect(const Message::CMessageConnectToServerPtr pMessage);
      void TakeStepPlayer(const Message::CMessageStepPlayerPtr pMessage);

   signals:
      void SendConfirmConnect(const Message::CMessageConfirmationConnectToServerPtr pMessage);
      void SendError(const Message::CMessageErrorPtr pMessage);
      void SendFinishGame(const Message::CMessageFinishGamePtr pMessage);
      void SendStateMap(const Message::CMessageStateMapPtr pMessage);
      void SendStartGame(const Message::CMessageStartMapGamePtr pMessage);
      void SendTimeToStart(const Message::CMessageTimeToStartGamePtr pMessage);

      void SendInInformation(const Message::CMessageInformationPtr pMessage);

   private:
      /// run timers + logic + generation map
      void startGame(
         const unsigned int timeToStart,
         const unsigned int widthMap,
         const unsigned int heigthMap,
         const unsigned int flySpeed,
         const unsigned int growSpeed,
         const std::string& namePlayer
         );


      CMapGame m_mapGame;
      std::vector<CPlayer> m_vPlayer;

   }; // class CSingleGameManager

} // namespace SingleGame

