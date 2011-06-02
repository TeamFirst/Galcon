#ifndef PLAYAREA_H
#define PLAYAREA_H

#include <QGraphicsView>
#include <vector>
#include <list>

class CGUIPlanet;
class CGUIFleet;


class CPlayArea : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CPlayArea(QWidget *parent = 0);
    void paintEvent ( QPaintEvent * event );
signals:

public slots:

private:
    std::vector<CGUIPlanet* > * m_planets;
    std::list<CGUIFleet* > * m_fleets;

};

#endif // PLAYAREA_H
