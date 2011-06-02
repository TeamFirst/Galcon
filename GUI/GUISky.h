#ifndef GUISKY_H
#define GUISKY_H

#include <QGraphicsItem>

class CGUISky : public QGraphicsItem
{

public:
    explicit CGUISky();

signals:

public slots:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget);

    virtual QRectF boundingRect() const;
};

#endif // GUISKY_H
