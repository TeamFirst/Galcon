#ifndef GUIPLANET_H
#define GUIPLANET_H

#include <QGraphicsItem>

class CGUIPlanet : public QGraphicsItem
{

public:
//    void SetCoord(const double, const double);

//    void SetCoef(const double *);

//    void SetFleet(unsigned int);

//    void SetRadius(unsigned int);

//    void SetPlayerID()



protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget);

    virtual QRectF boundingRect() const;


signals:

public slots:
private:
    double m_xLog;
    double m_yLog;
    const double * mp_K;
    unsigned int m_ownerID;
    const unsigned m_ourPlayer;


};

#endif // GUIPLANET_H
