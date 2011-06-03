#ifndef GUIFLEET_H
#define GUIFLEET_H
#include <QPainter>
#include "Game/Fleet.h"

class CGUIFleet
{
public:
    CGUIFleet(){};
    CGUIFleet(CFleet*);

    void Draw(QPainter*);

private:
    CFleet* m_fleet;
};

#endif // GUIFLEET_H
