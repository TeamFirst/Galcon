#pragma once

#include <QSharedPointer>

#include "MessageItf.h"

namespace Message
{
   struct CMessageFinishGame;

   typedef QSharedPointer<CMessageFinishGame> CMessageFinishGamePtr;

   struct CMessageFinishGame : public IMessage
   {
      unsigned int m_playerID;

   protected:

      virtual std::string toString() const
      {
         return std::string();
      }

   }; // struct CMessageFinishGame
} // namespace Message
