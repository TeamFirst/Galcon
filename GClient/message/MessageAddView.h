#pragma once

#include <QSharedPointer>

#include "MessageItf.h"

namespace Message
{
   class ISceneUpdates;
   struct CMessageAddView;

   typedef QSharedPointer<CMessageAddView> CMessageAddViewPtr;

   struct CMessageAddView : public IMessage
   {
      ISceneUpdates* m_view;

   protected:

      virtual std::string toString() const
      {
         return std::string();
      }

   }; // struct CMessageAddView   

} // namespace Message
