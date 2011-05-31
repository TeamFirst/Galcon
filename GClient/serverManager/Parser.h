#pragma once

namespace ServerManagerDecl
{
   class CParser
   {
   public:

      enum ETypeMessage
      {
         eConfirmConnect,
         eError,
         eFinishGame,
         eStateMap,
         eStartGame,
         eTimeToStart
      };

      CParser();
      ~CParser();

   }; // class CParser
} // namespace ServerManagerDecl
