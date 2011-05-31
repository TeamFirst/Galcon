#pragma once

#include <QSharedPointer>

#include "MessageItf.h"

namespace Message
{
   struct CMessaheTimeToStartGame;

   typedef QSharedPointer<CMessaheTimeToStartGame> CMessaheTimeToStartGamePtr;

   struct CMessaheTimeToStartGame : public IMessage
   {
      unsigned int m_second;

   protected:

      virtual std::string toString() const
      {
         return std::string();
      }

   }; // struct CMessaheTimeToStartGame

}; // namespace Message
