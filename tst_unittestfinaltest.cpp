#include <QtCore/QString>
#include <QtTest/QtTest>

#include "Planet.h"
#include "Fleet.h"
#include "Space.h"

class UnitTestFinalTest : public QObject
{
    Q_OBJECT

public:
    UnitTestFinalTest();

private Q_SLOTS:
    void initTestCase();
    void testCasePlanet();
    void testCaseFleet();
    void testCaseSpace();
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

   CPlanet* fr2 = new CPlanet(1, 10, 10, 5, 100500, 1);
   CPlanet* to2 = new CPlanet(2, 10, 20, 15, 100, 2);
   CFleet fl2(0, fr2, to2, 1, 500, 50);
   fl2.IncreaseWay(5);
   fl2.GetPosition(x,y);
   QVERIFY2((x - 200 < eps) && (y - 15 < eps), "Failture increase procent");

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

void UnitTestFinalTest::testCaseSpace()
{

   Message::CPlanetStartData data = {100, 1, 5 , 0, 10, 1};
   Message::CPlanetStartData data2 = {200, 2, 15 , 10, 20, 2};
   std::vector<Message::CPlanetStartData> vec;
   vec.push_back(data);
   vec.push_back(data2);
   Message::CPlayerStartData pl1 = {1, "Vasya"};
   Message::CPlayerStartData pl2 = {2, "Petya"};
   std::vector<Message::CPlayerStartData> plVec;
   plVec.push_back(pl1);
   plVec.push_back(pl2);
   CSpace* sp = new CSpace(2, 1, 300, 400, vec);
   std::vector<CPlanet*> planets(sp->GetPlanets());

   QVERIFY2(planets.size() == 2, "Fail add planets to space");

   QVERIFY2(planets[0]->GetArmy() == 100 , "Fail add correct planet to space");


}

QTEST_APPLESS_MAIN(UnitTestFinalTest);

#include "tst_unittestfinaltest.moc"
