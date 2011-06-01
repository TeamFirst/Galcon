#pragma once

#include <string>
#include <vector>

#include "message/MessageConnectToServer.h"
#include "message/MessageError.h"
#include "message/MessageFinishGame.h"
#include "message/MessageStateMap.h"
#include "message/MessageStartMapGame.h"
#include "message/MessageTimeToStartGame.h"

namespace ServerManagerDecl
{
   class CParser
   {
   public:

      enum ETypeMessage
      {
         eUnknown,
         eConfirmConnect,
         eError,
         eFinishGame,
         eStateMap,
         eStartGame,
         eTimeToStart
      };

      CParser();
      ~CParser();

      ETypeMessage CheckTypeMessage(const std::string sMes) const;

      const Message::CMessageConfirmationConnectToServerPtr
         ParseMConfirmConnect(const std::string sMes);

      const Message::CMessageErrorPtr
         ParseMError(const std::string sMes);

      const Message::CMessageFinishGamePtr
         ParseMFinishGame(const std::string sMes);

      const Message::CMessageStateMapPtr
         ParseMStateMap(const std::string sMes);

      const Message::CMessageStartMapGamePtr
         ParseMStartMapGame(const std::string sMes);

      const Message::CMessageTimeToStartGamePtr
         ParseMTimeToStartGame(const std::string sMes);

   private:
      std::vector< std::pair<std::string, ETypeMessage> > m_vMsgStrEnumType;

   }; // class CParser
} // namespace ServerManagerDecl
