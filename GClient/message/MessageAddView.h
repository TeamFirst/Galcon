#pragma once

#include <QSharedPointer>

namespace Message
{
   class ISceneUpdates;
   struct CMessageAddView;

   typedef QSharedPointer<CMessageAddView> CMessageAddViewPtr;

   struct CMessageAddView
   {
      ISceneUpdates* m_view;

   }; // struct CMessageAddView   

} // namespace Message
