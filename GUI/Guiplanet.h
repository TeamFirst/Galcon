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
    CPlanet* GetPlanet() const;
    void MakeActive();
    void ReleaseActive();
    bool IsActive() const;

private:
    CPlanet* m_planet;
    bool m_active;
};

#endif // GUIPLANET_H
