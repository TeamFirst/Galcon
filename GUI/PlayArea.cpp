#include "PlayArea.h"
#include <QPaintEvent>
CPlayArea::CPlayArea(QWidget *parent) :
    QGraphicsView(parent)
{
}
void CPlayArea::paintEvent ( QPaintEvent * event )
{
    QGraphicsView::paintEvent(event);
}
