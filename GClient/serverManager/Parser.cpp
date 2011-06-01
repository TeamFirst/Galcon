#include <stdlib.h>
#include <QString>

#include "Parser.h"

namespace ServerManagerDecl
{
/// constructor
   CParser::CParser()
   {
      m_vMsgStrEnumType.push_back(std::make_pair("SC_CONNID", eConfirmConnect));
      m_vMsgStrEnumType.push_back(std::make_pair("SC_ERR", eError));
      m_vMsgStrEnumType.push_back(std::make_pair("SC_FINISH", eFinishGame));
      m_vMsgStrEnumType.push_back(std::make_pair("SC_STATE", eStateMap));
      m_vMsgStrEnumType.push_back(std::make_pair("SC_START", eStartGame));
      m_vMsgStrEnumType.push_back(std::make_pair("SC_TIMETOSTART", eTimeToStart));
   }

   CParser::~CParser()
   {
   }

/// function for parse
   CParser::ETypeMessage CParser::CheckTypeMessage(const std::string& sMes) const
   {
      std::vector< std::pair<std::string, ETypeMessage> >::const_iterator it =
            m_vMsgStrEnumType.begin();

      for(; it != m_vMsgStrEnumType.end(); ++it)
      {
         if(0 == sMes.find(it->first))
         {
            return (*it).second;
         }
      }
      return eUnknown;
   }

   const Message::CMessageConfirmationConnectToServerPtr
      CParser::ParseMConfirmConnect(const std::string& sMes)
   {      
      /// SC_CONNID#3##
      char sBuf[20];
      std::string::size_type pos1 = sMes.find_first_of('#',1);
      std::string::size_type pos2 = sMes.find_first_of('#', pos1 + 1);
      sMes.copy(sBuf, pos2 - pos1 - 1, pos1 +1);

      Message::CMessageConfirmationConnectToServerPtr ptr(
         new Message::CMessageConfirmationConnectToServer);

      ptr->m_playerID = QString(sBuf).toULong();

      return ptr;
   }

   const Message::CMessageErrorPtr
      CParser::ParseMError(const std::string& sMes)
   {
      /// SC_ERR#Player1 disconnected!##
      // std::string m_strError;
      std::string::size_type pos1 = sMes.find_first_of('#');
      std::string::size_type pos2 = sMes.find_first_of('#', pos1 + 1);

      Message::CMessageErrorPtr ptr( new Message::CMessageError);

      std::string str(sMes, pos2 - pos1 - 1, pos1 +1);

      return ptr;
   }

   const Message::CMessageFinishGamePtr
      CParser::ParseMFinishGame(const std::string& sMes)
   {
      return Message::CMessageFinishGamePtr(
         new Message::CMessageFinishGame);
   }

   const Message::CMessageStateMapPtr
      CParser::ParseMStateMap(const std::string& sMes)
   {
      return Message::CMessageStateMapPtr(
         new Message::CMessageStateMap);
   }

   const Message::CMessageStartMapGamePtr
      CParser::ParseMStartMapGame(const std::string& sMes)
   {
      return Message::CMessageStartMapGamePtr(
         new Message::CMessageStartMapGame);
   }

   const Message::CMessageTimeToStartGamePtr
      CParser::ParseMTimeToStartGame(const std::string& sMes)
   {
      return Message::CMessageTimeToStartGamePtr(
         new Message::CMessageTimeToStartGame);
   }

} //namespace ServerManagerDecl


