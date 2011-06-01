#include "Planet.h"
#include "Fleet.h"
#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char* argv[])
{
   CPlanet pl(0, 0, 0, 12, 100500, 7);
   CPlanet* fr = new CPlanet(1, 0, 10, 5, 100500, 1);
   CPlanet* to = new CPlanet(2, 10, 20, 15, 100, 2);
   CFleet fl(0, fr, to, 1, 500, 0);
   double x(0), y(0);
   fl.GetPosition(x,y);
   //cout<<floor(x)<<floor(y);
   cout<<to->GetArmy()<<fr->GetArmy()<<"\n";
   fl.SetPercent(200);
   fl.GetPosition(x,y);
   cout<<to->GetArmy()<<to->GetPlayerId();
   return 0;
}
