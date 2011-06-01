#ifndef PLAYAREA_H
#define PLAYAREA_H

#include <QGraphicsView>
#include <vector>
#include <list>
#include "../Planet.h"
#include "../Fleet.h"
#include "GUIFleet.h"
#include "GUIPlanet.h"

class CPlayArea : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CPlayArea(QWidget *parent = 0);

signals:

public slots:

private:
    std::vector<CGUIPlanet *> m_planets;
    std::list<CGUIFleet* > m_fleets;

};

#endif // PLAYAREA_H
