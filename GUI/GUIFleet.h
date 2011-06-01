#ifndef GUIPLANET_H
#define GUIPLANET_H

#include <QGraphicsItem>
#include "../Planet.h"
#include "../Fleet.h"
class CGUIFleet : public QObject, public QGraphicsItem
{

public:
    CGUIFleet(const CFleet *, const double * K, QObject * parent = 0);


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

#endif // GUIPLANET_H
