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
      size_t pos1 = sMes.find('#');
      size_t pos2 = sMes.find('#', pos1 + 1);

      Message::CMessageConfirmationConnectToServerPtr ptr(
         new Message::CMessageConfirmationConnectToServer);

      ptr->m_playerID = convertStdStrToUInt(sMes.substr(pos1 + 1, pos2 - pos1 - 1));

      return ptr;
   }

   const Message::CMessageErrorPtr
      CParser::ParseMError(const std::string& sMes)
   {
      /// SC_ERR#Player1 disconnected!##
      // std::string m_strError;
      size_t pos1 = sMes.find_first_of('#');
      size_t pos2 = sMes.find_first_of('#', pos1 + 1);

      Message::CMessageErrorPtr ptr( new Message::CMessageError);

      ptr->m_strError = sMes.substr(pos1 + 1, pos2 - pos1 - 1);

      return ptr;
   }

   const Message::CMessageFinishGamePtr
      CParser::ParseMFinishGame(const std::string& sMes)
   {
      /// SC_FINISH#2##
      // unsigned int m_playerID;
      size_t pos1 = sMes.find_first_of('#');
      size_t pos2 = sMes.find_first_of('#', pos1 + 1);

      Message::CMessageFinishGamePtr ptr(
         new Message::CMessageFinishGame);

      ptr->m_playerID = QString(sMes.substr(pos1 + 1, pos2 - pos1 - 1).c_str()).toUInt();

      return ptr;
   }

   const Message::CMessageStateMapPtr
      CParser::ParseMStateMap(const std::string& sMes)
   {
      /// "SC_STATE#(1,1,20)(2,0,15)(3,0,8)(4,4,8)#(1,2,4,2,12,0)(2,2,3,2,24,0)##";
      // std::vector<CStateFleet> m_fleetState;
         // unsigned int m_countFleet;
         // unsigned int m_fleetID;
         // unsigned int m_percentRoute;
         // unsigned int m_planetFinishID;
         // unsigned int m_planetStartID;
         // unsigned int m_playerID;
      // std::vector<CStatePlanet> m_planetState;
         // unsigned int m_countFleet;
         // unsigned int m_planetID;
         // unsigned int m_playerID;
      Message::CMessageStateMapPtr ptr(
         new Message::CMessageStateMap);

      size_t posBPart = sMes.find('#');
      size_t posEPart = sMes.find('#', posBPart + 1);
      /// parse planet state
      for(;;)
      {
      }

      /// parse fleet state
      for(;;)
      {
      }

      return ptr;
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
      /// SC_TIMETOSTART#9##
      // unsigned int m_second;
      size_t pos1 = sMes.find_first_of('#');
      size_t pos2 = sMes.find_first_of('#', pos1 + 1);

      Message::CMessageTimeToStartGamePtr ptr(
         new Message::CMessageTimeToStartGame);

      ptr->m_second = convertStdStrToUInt(sMes.substr(pos1 + 1, pos2 - pos1 - 1));

      return ptr;
   }

   unsigned int CParser::convertStdStrToUInt(const std::string& str)
   {
      return QString(str.c_str()).toUInt();
   }

   void CParser::parseVectorUInt(
      const std::string& sMes,
      const std::string& separator,
      const size_t posF,
      const size_t posE)
   {
      m_vParseSubMes.clear();
      size_t posFB = posF;
      size_t posSB = sMes.find(separator, posFB + 1);
      for(; (posSB != std::string::npos) && (posSB < posE);
          posFB = posSB , posSB = sMes.find(separator, posFB + 1))
      {
         m_vParseSubMes.push_back(
                  convertStdStrToUInt(sMes.substr(posFB + 1, posSB - posFB - 1)));
      }

      m_vParseSubMes.push_back(
               convertStdStrToUInt(sMes.substr(posFB + 1, sMes.size() - posFB - 1)));
   }

} //namespace ServerManagerDecl


