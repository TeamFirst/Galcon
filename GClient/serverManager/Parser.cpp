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
      Message::CStatePlanet tempPlanet;
      Message::CStateFleet tempFleet;

      Message::CMessageStateMapPtr ptr(
         new Message::CMessageStateMap);

      size_t posBPart = 0;
      size_t posEPart = 0;
      size_t posFBr = 0;
      size_t posSBr = 0;
      /// parse planet state
      posBPart = sMes.find('#', posEPart + 1);
      posEPart = sMes.find('#', posBPart + 1);
      posFBr = sMes.find('(', posBPart);
      posSBr = sMes.find(')', posBPart + 1);
      for(; posFBr < posEPart;
          posFBr = sMes.find('(', posSBr),
          posSBr = sMes.find(')', posFBr + 1))
      {
         parseVectorUInt(sMes, ",", posFBr, posSBr);

         tempPlanet.m_planetID = m_vParseSubMes[0];
         tempPlanet.m_playerID = m_vParseSubMes[1];
         tempPlanet.m_countFleet = m_vParseSubMes[2];

         ptr->m_planetState.push_back(tempPlanet);
      }

      /// parse fleet state
      posBPart = posEPart;
      posEPart = sMes.find('#', posBPart + 1);
      posFBr = sMes.find('(', posBPart);
      posSBr = sMes.find(')', posBPart + 1);

      for(; posFBr < posEPart;
         posFBr = sMes.find('(', posSBr),
         posSBr = sMes.find(')', posFBr + 1))
      {
         parseVectorUInt(sMes, ",", posFBr, posSBr);

         tempFleet.m_fleetID = m_vParseSubMes[0];
         tempFleet.m_playerID = m_vParseSubMes[1];
         tempFleet.m_planetStartID = m_vParseSubMes[2];
         tempFleet.m_planetFinishID = m_vParseSubMes[3];
         tempFleet.m_countFleet = m_vParseSubMes[4];
         tempFleet.m_percentRoute = m_vParseSubMes[5];

         ptr->m_planetState.push_back(tempPlanet);
      }

      return ptr;
   }

   const Message::CMessageStartMapGamePtr
      CParser::ParseMStartMapGame(const std::string& sMes)
   {
      // SC_START#100#80#2#25#
      // (1,1,20,40,12,20)(2,0,40,20,10,15)(3,0,50,70,45,8)(4,2,80,60,12,20)
      // #(1,Red Fox)(2,Star_123456)##";
      Message::CMessageStartMapGamePtr ptr(
         new Message::CMessageStartMapGame);

      size_t posBPart = 0;
      size_t posEPart = 0;
      size_t posFBr = 0;
      size_t posSBr = 0;

      // unsigned int m_mapX;
      posBPart = sMes.find('#');
      posEPart = sMes.find('#', posBPart + 1);
      ptr->m_mapX = convertStdStrToUInt(
               sMes.substr(posBPart +1, posEPart - posBPart -1));
      // unsigned int m_mapY;
      posBPart = posEPart;
      posEPart = sMes.find('#', posBPart + 1);
      ptr->m_mapY = convertStdStrToUInt(
               sMes.substr(posBPart +1, posEPart - posBPart -1));
      // unsigned int m_growV;
      posBPart = posEPart;
      posEPart = sMes.find('#', posBPart + 1);
      ptr->m_growV = convertStdStrToUInt(
               sMes.substr(posBPart +1, posEPart - posBPart -1));
      // unsigned int m_flyV;
      posBPart = posEPart;
      posEPart = sMes.find('#', posBPart + 1);
      ptr->m_flyV = convertStdStrToUInt(
               sMes.substr(posBPart +1, posEPart - posBPart -1));

      // std::vector<CPlanetStartData> m_planetData;
      Message::CPlanetStartData tempPlanet;

      posBPart = posEPart;
      posEPart = sMes.find('#', posBPart + 1);
      posFBr = sMes.find('(', posBPart);
      posSBr = sMes.find(')', posBPart + 1);

      for(; posFBr < posEPart;
         posFBr = sMes.find('(', posSBr),
         posSBr = sMes.find(')', posFBr + 1))
      {
         parseVectorUInt(sMes, ",", posFBr, posSBr);
         tempPlanet.m_planetID = m_vParseSubMes[0];
         tempPlanet.m_playerID = m_vParseSubMes[1];
         tempPlanet.m_planetX = m_vParseSubMes[2];
         tempPlanet.m_planetY = m_vParseSubMes[3];
         tempPlanet.m_planetR = m_vParseSubMes[4];
         tempPlanet.m_countFleet = m_vParseSubMes[5];

         ptr->m_planetData.push_back(tempPlanet);
      }

      // std::vector<CPlayerStartData> m_playerData;
         // unsigned int m_playerID;
         // std::string m_playerName;
      Message::CPlayerStartData tempPlayer;

      posBPart = posEPart;
      posEPart = sMes.find('#', posBPart + 1);
      posFBr = sMes.find('(', posBPart);
      posSBr = sMes.find(')', posBPart + 1);

      for(; posFBr < posEPart;
         posFBr = sMes.find('(', posSBr),
         posSBr = sMes.find(')', posFBr + 1))
      {
         parseVectorUInt(sMes, ",", posFBr, posSBr);
         tempPlayer.m_playerID = m_vParseSubMes[0];
         //tempPlayer.m_playerID = m_vParseSubMes[1];

         ptr->m_playerData.push_back(tempPlayer);
      }

      return ptr;
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
               convertStdStrToUInt(sMes.substr(posFB + 1, posE - posFB - 1)));
   }

} //namespace ServerManagerDecl


