#pragma once

#include <QGraphicsItem>
#include "Game/Planet.h"
#include "Game/Fleet.h"
class CGUIFleet : public QObject, public QGraphicsItem
{

public:
    CGUIFleet(const CFleet *, const double * K, QObject * parent = 0);
    const CFleet * GetFleet() const
    {
        return m_fleet;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget);

    virtual QRectF boundingRect() const;


signals:

public slots:
private:
    double m_percent;
    QColor col;
    double m_x, m_y, m_r;
    const double * mp_K;
    const CFleet * m_fleet;




};


