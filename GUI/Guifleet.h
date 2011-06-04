#ifndef GUIFLEET_H
#define GUIFLEET_H
#include <QPainter>
#include "Game/Fleet.h"

class CGUIFleet
{
public:
    CGUIFleet(){};
    CGUIFleet(Game::CFleet*);

    void Draw(QPainter*);

private:
    Game::CFleet* m_fleet;
};

#endif // GUIFLEET_H
