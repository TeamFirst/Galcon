#include "GUIPlanet.h"
#include "GUIFleet.h"

CGUIFleet::CGUIFleet(const CPFleet * fleet, const double * K, QObject * parent = 0):
        QObject(parent),
        mp_K(K),
        m_fleet(fleet)
{


}
QRectF CGUIFleet::boundingRect() const
{

    m_fleet->GetPosition(m_x, m_y);

    m_x = m_x * (*mp_K);
    m_y = m_y * (*mp_K);

    m_r = 20 * (*mp_K);
    QRectF rect(m_x - m_r, m_y - m_r, 2 * m_r, 2 * m_r);
}
void CGUIFleet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    painter->setPen(Qt::black);
    //QBrush b(m_color);

    QBrush b(Qt::cyan);
    painter->setBrush(b);
    painter->drawEllipse(m_x, m_y, m_r , m_r );
    //QBrush b(Qt::NoBrush);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(m_x, m_y, m_r / 2, m_r / 2);


    painter->drawText(m_x, m_y, QVariant(m_fleet->GetShipCount()).toString());

}

