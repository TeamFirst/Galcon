#ifndef GUIPLANET_H
#define GUIPLANET_H
#include <QPainter>
#include "Game/Planet.h"

class CGUIPlanet
{
public:
   CGUIPlanet(){}
    CGUIPlanet(CPlanet* planet);

    void Draw(QPainter*);

private:
    CPlanet* m_planet;
    bool is_active;
};

#endif // GUIPLANET_H
