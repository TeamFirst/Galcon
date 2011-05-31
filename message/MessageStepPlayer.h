#pragma once

#include <vector>
#include <string>
#include <stdlib.h>
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

   //protected:

      virtual std::string toString() const
      {
         char sBuf[20];
         std::string sMes("CS_STEP#");
         std::vector<unsigned int>::const_iterator it = m_startPlanetID.begin();
         for(; it != m_startPlanetID.end(); ++it)
         {
            sMes.append("(");
            sMes.append(ulltoa(*it, sBuf, 10));
            sMes.append(")");
         }
         sMes.append("#");
         sMes.append(ulltoa(m_percent, sBuf, 10));
         sMes.append("#");
         sMes.append(ulltoa(m_finishPlanetID, sBuf, 10));
         sMes.append("##");

         return sMes;
      }

   }; // struct CMessageStepPlayer

} // namespace Message
