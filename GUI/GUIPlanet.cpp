#include <QRectF>
#include <QPainter>
#include <QVariant>
#include "GUIPlanet.h"
CGUIPlanet::CGUIPlanet(const CPlanet * planet, const double * K, QObject * parent = 0):
        QObject(parent),
        mp_K(K),
        m_planet(planet)
{


}
QRectF CGUIPlanet::boundingRect() const
{


    m_planet->GetPosition(m_x, m_y);

    m_x = m_x * (*mp_K);
    m_y = m_y * (*mp_K);

    m_r = (m_planet->GetRadius()) * (*mp_K);
    QRectF rect(m_x - m_r, m_y - m_r, 2 * m_r, 2 * m_r);
}
void CGUIPlanet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    painter->setPen(Qt::black);
    //QBrush b(m_color);
    if (m_selected)
    {
        QBrush b(Qt::green);
        painter->setBrush(b);
        painter->drawEllipse(m_x, m_y, m_r * 1.3, m_r * 1.3);
        //QBrush b(Qt::NoBrush);
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(m_x, m_y, m_r * 1.2, m_r * 1.2);

    }
    QBrush b(Qt::blue);
    painter->setBrush(b);
    painter->drawEllipse(m_x , m_y , m_r, m_r);
    painter->drawText(m_x, m_y, QVariant(m_planet->GetArmy()).toString());


}
void CGUIPlanet::SetSelected(bool s)
{
    m_selected = s;

}
