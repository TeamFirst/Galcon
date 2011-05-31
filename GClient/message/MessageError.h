#pragma once

#include <string>
#include <QSharedPointer>

#include "MessageItf.h"

namespace Message
{
   struct CMessageError;

   typedef QSharedPointer<CMessageError> CMessageErrorPtr;

   struct CMessageError : public IMessage
   {
      std::string m_strError;

   protected:

      virtual std::string toString() const
      {
         return std::string();
      }

   }; // struct CMessageError
} // namespace Message
