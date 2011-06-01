#ifndef GUIPLANET_H
#define GUIPLANET_H

#include <QColor>
#include <QGraphicsItem>

class CPlanet;

class CGUIPlanet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    CGUIPlanet(const CPlanet *, const double * K, QObject * parent = 0);

    const CPlanet * GetPlanet() const
    {
        return m_planet;
    }
//    void SetCoord(const double, const double);

//    void SetCoef(const double *);

//    void SetFleet(unsigned int);

//    void SetRadius(unsigned int);

//    void SetPlayerID()

    void SetSelected(bool s);


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget);

    virtual QRectF boundingRect() const;


signals:

public slots:
private:
    QColor col;
    bool m_selected;
    double m_x, m_y, m_r;
    const double * mp_K;
    const CPlanet * m_planet;
};

#endif // GUIPLANET_H
