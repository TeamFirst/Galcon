#pragma once

#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
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
         char sBuf[20];
         std::string sMes("CS_STEP#");
         QString temp;
         std::vector<unsigned int>::const_iterator it = m_startPlanetID.begin();
         for(; it != m_startPlanetID.end(); ++it)
         {
            sMes.append("(");
            temp.setNum(*it, 10);
            sMes.append(temp.toStdString());
            sMes.append(")");
         }
         sMes.append("#");
         temp.clear();
         temp.setNum(m_percent, 10);
         sMes.append(temp.toStdString());
         sMes.append("#");
         temp.clear();
         temp.setNum(m_finishPlanetID, 10);
         sMes.append(temp.toStdString());

         sMes.append("##");

         return sMes;
      }

   }; // struct CMessageStepPlayer

} // namespace Message
