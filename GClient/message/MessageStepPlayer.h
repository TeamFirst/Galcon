#pragma once

#include <vector>
#include <QSharedPointer>

#include "MessageItf.h"

namespace Message
{
   struct CMessageStepPlayer;

   typedef QSharedPointer<CMessageStepPlayer> CMessageStepPlayerPtr;

   struct CMessageStepPlayer : public IMessage
   {
      unsigned int m_finishPlanetID;
      unsigned int m_percent;
      std::vector<unsigned int> m_startPlanetID;

   protected:

      virtual std::string toString() const
      {
         return std::string();
      }

   }; // struct CMessageStepPlayer

} // namespace Message
