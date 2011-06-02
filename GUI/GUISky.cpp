#include "GUISky.h"
#include <QPainter>
CGUISky::CGUISky()
{
}
void CGUISky::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
{
    painter->setPen(Qt::red);
    painter->drawEllipse(10, 10, 10, 10);

}

QRectF CGUISky::boundingRect() const
{
    return QRectF(0,0, 20, 20);

}
