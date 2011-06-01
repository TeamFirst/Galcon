#include <QtCore/QString>
#include <QtTest/QtTest>

class UnitTestParserTest : public QObject
{
    Q_OBJECT

public:
    UnitTestParserTest();

private Q_SLOTS:
    void testCase1();
};

UnitTestParserTest::UnitTestParserTest()
{
}

void UnitTestParserTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(UnitTestParserTest);

#include "tst_unittestparsertest.moc"
