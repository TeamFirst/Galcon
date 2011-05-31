#pragma once

#include <QSharedPointer>

namespace Message
{
   struct CMessaheTimeToStartGame;

   typedef QSharedPointer<CMessaheTimeToStartGame> CMessaheTimeToStartGamePtr;

   struct CMessaheTimeToStartGame
   {
      unsigned int m_second;  

   }; // struct CMessaheTimeToStartGame

}; // namespace Message
