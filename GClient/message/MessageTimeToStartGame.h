#pragma once

#include <QSharedPointer>

#include "MessageItf.h"

namespace Message
{
   struct CMessageTimeToStartGame;

   typedef QSharedPointer<CMessageTimeToStartGame> CMessageTimeToStartGamePtr;

   struct CMessageTimeToStartGame : public IMessage
   {
      unsigned int m_second;

   protected:

      virtual std::string toString() const
      {
         return std::string();
      }

   }; // struct CMessaheTimeToStartGame

}; // namespace Message
