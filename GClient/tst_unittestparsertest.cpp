#include <QtCore/QString>
#include <QtTest/QtTest>

#include <string>

#include "serverManager/Parser.h"

class UnitTestParserTest : public QObject
{
    Q_OBJECT

public:
    UnitTestParserTest();

private Q_SLOTS:
    void testCParser_CheckTypeMessage();

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

}

QTEST_APPLESS_MAIN(UnitTestParserTest);

#include "tst_unittestparsertest.moc"
