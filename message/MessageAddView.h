#pragma once

#include <QSharedPointer>

class ISceneUpdates;

namespace Message
{   
   struct CMessageAddView;

   typedef QSharedPointer<CMessageAddView> CMessageAddViewPtr;

   struct CMessageAddView
   {
      ISceneUpdates* m_view;

   }; // struct CMessageAddView   

} // namespace Message
