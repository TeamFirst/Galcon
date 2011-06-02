#include <QtCore/QString>
#include <QtTest/QtTest>

#include <string>

#include "serverManager/Parser.h"
#include "message/MessageConnectToServer.h"
#include "message/MessageError.h"
#include "message/MessageFinishGame.h"
#include "message/MessageStateMap.h"
#include "message/MessageStartMapGame.h"
#include "message/MessageTimeToStartGame.h"

class UnitTestParserTest : public QObject
{
    Q_OBJECT

public:
    UnitTestParserTest();

private Q_SLOTS:
    void testCParser_CheckTypeMessage();

    void testCParser_ParseMConfirmConnect();

    void testCParser_ParseMError();

    void testCParser_ParseMFinishGame();

    void testCParser_ParseMStateMap();

    void testCParser_ParseMStartMapGame();

    void testCParser_ParseMTimeToStartGame();

private:
    ServerManagerDecl::CParser m_parser;

};

UnitTestParserTest::UnitTestParserTest()
{
}

void UnitTestParserTest::testCParser_CheckTypeMessage()
{  
   std::string sMes;
   sMes = "SC_CONNID#3##";
   QVERIFY2(m_parser.CheckTypeMessage(sMes) == ServerManagerDecl::CParser::eConfirmConnect,
            "Failure eConfirmConnect");

   sMes = "SC_TIMETOSTART#9##";
   QVERIFY2(m_parser.CheckTypeMessage(sMes) == ServerManagerDecl::CParser::eTimeToStart,
            "Failure eTimeToStart");

   sMes = "SC_START#100#80#2#25#(1,1,20,40,12,20)(2,0,40,20,10,15)(3,0,50,70,45,8)(4,2,80,60,12,20)#(1,Red Fox)(2,Star_123456)##";
   QVERIFY2(m_parser.CheckTypeMessage(sMes) == ServerManagerDecl::CParser::eStartGame,
            "Failure eStartGame");

   sMes = "SC_STATE#(1,1,20)(2,0,15)(3,0,8)(4,4,8)#(1,2,4,2,12,0)(2,2,3,2,24,0)##";
   QVERIFY2(m_parser.CheckTypeMessage(sMes) == ServerManagerDecl::CParser::eStateMap,
            "Failure eStateMap");

   sMes = "SC_FINISH#2##";
   QVERIFY2(m_parser.CheckTypeMessage(sMes) == ServerManagerDecl::CParser::eFinishGame,
            "Failure eFinishGame");

   sMes = "SC_ERR#Player1 disconnected!##";
   QVERIFY2(m_parser.CheckTypeMessage(sMes) == ServerManagerDecl::CParser::eError,
            "Failure eError");

   sMes = "ERROR_MESSAGE_TYPE#Player1 disconnected!##";
   QVERIFY2(m_parser.CheckTypeMessage(sMes) == ServerManagerDecl::CParser::eUnknown,
            "Failure eUnknown");

}

void UnitTestParserTest::testCParser_ParseMConfirmConnect()
{
   std::string sMes = "SC_CONNID#3##";
   Message::CMessageConfirmationConnectToServerPtr ptr(
      new Message::CMessageConfirmationConnectToServer);

   m_parser.ParseMConfirmConnect(sMes);
}

void UnitTestParserTest::testCParser_ParseMError()
{
   std::string sMes = "SC_ERR#Player1 disconnected!##";
   Message::CMessageErrorPtr ptr(
      new Message::CMessageError);

   m_parser.ParseMError(sMes);
}

void UnitTestParserTest::testCParser_ParseMFinishGame()
{
   std::string sMes = "SC_FINISH#2##";
   Message::CMessageFinishGamePtr ptr(
      new Message::CMessageFinishGame);

   m_parser.ParseMFinishGame(sMes);
}

void UnitTestParserTest::testCParser_ParseMStateMap()
{
   std::string sMes = "SC_STATE#(1,1,20)(2,0,15)(3,0,8)(4,4,8)#(1,2,4,2,12,0)(2,2,3,2,24,0)##";
   Message::CMessageStateMapPtr ptr(
      new Message::CMessageStateMap);

   m_parser.ParseMStateMap(sMes);
}

void UnitTestParserTest::testCParser_ParseMStartMapGame()
{
   std::string sMes = "SC_START#100#80#2#25#(1,1,20,40,12,20)(2,0,40,20,10,15)(3,0,50,70,45,8)(4,2,80,60,12,20)#(1,Red Fox)(2,Star_123456)##";
   Message::CMessageStartMapGamePtr ptr(
      new Message::CMessageStartMapGame);

   m_parser.ParseMStartMapGame(sMes);
}

void UnitTestParserTest::testCParser_ParseMTimeToStartGame()
{
   std::string sMes = "SC_TIMETOSTART#9##";
   Message::CMessageTimeToStartGamePtr ptr(
      new Message::CMessageTimeToStartGame);

   m_parser.ParseMTimeToStartGame(sMes);
}

QTEST_APPLESS_MAIN(UnitTestParserTest);

#include "tst_unittestparsertest.moc"
