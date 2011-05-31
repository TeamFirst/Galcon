#include <QtCore/QString>
#include <QtTest/QtTest>

#include "Planet.h"
#include "Fleet.h"

class UnitTestFinalTest : public QObject
{
    Q_OBJECT

public:
    UnitTestFinalTest();

private Q_SLOTS:
    void initTestCase();
    void testCasePlanet();
    void testCaseFleet();
};

UnitTestFinalTest::UnitTestFinalTest()
{
}

void UnitTestFinalTest::initTestCase()
{

}

void UnitTestFinalTest::testCasePlanet()
{
   CPlanet pl(1, 0, 10, 5, 100500, 2);
   QVERIFY2(pl.GetPlayerId() == 2, "Failure player id");
   QVERIFY2(pl.GetArmy() == 100500, "Failure army");
   unsigned int x(0), y(0);
   pl.GetPosition(x,y);
   QVERIFY2((x==0) && (y==10), "Failure coords");
   QVERIFY2(pl.GetRadius() == 5, "Failure radius");

   pl.SetArmy(400);
   QVERIFY2(pl.GetArmy() == 400, "Failure army");
   pl.SetPlayer(3);
   QVERIFY2(pl.GetPlayerId() == 3, "Failure playerId");
}

void UnitTestFinalTest::testCaseFleet()
{
   const double eps = 0.0001;
   CPlanet* fr = new CPlanet(1, 0, 10, 5, 100500, 1);
   CPlanet* to = new CPlanet(2, 10, 20, 15, 100, 2);
   CFleet fl(0, fr, to, 1, 500, 50);
   QVERIFY2(fl.GetPlayerId() == 1, "Failture player");
   QVERIFY2(fl.GetShipCount() == 500, "Failture shipcount");
   double x(0), y(0);
   fl.GetPosition(x,y);
   QVERIFY2((x - 5 < eps) && (y - 15 < eps), "Failture count real position");

   fl.IncreaseProcent(25);
   fl.GetPosition(x,y);
   QVERIFY2((x - 7.5 < eps) && (y - 17.5 < eps), "Failture increase procent");

   fl.SetPercent(10);
   fl.GetPosition(x,y);
   QVERIFY2((x - 1 < eps) && (y - 11 < eps), "Failture set procent");

   fl.SetPercent(100);
   QVERIFY2(fl.ReachedDestination(), "Failture reach destination");

   fl.SetPercent(200);
   fl.GetPosition(x,y);
   QVERIFY2((x - 10 < eps) && (y - 20 < eps) && fl.ReachedDestination() ,
            "Failture 100% destination");
   QVERIFY2(to->GetPlayerId() == 1, "Failture capture planet");
   QVERIFY2(to->GetArmy() == 400, "Failture capture planet");


}

QTEST_APPLESS_MAIN(UnitTestFinalTest);

#include "tst_unittestfinaltest.moc"
