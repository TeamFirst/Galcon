#ifndef GUI_H
#define GUI_H

#include <QObject>
#include "Message.h"
#include "enterwindow.h"
class CGUI : public QObject
{
    Q_OBJECT
public:
    explicit CGUI(QObject *parent = 0);

public slots:
    void TakeError(pIMessage mess);

    void TakeFinishGame(pIMessage mess);

    void TakeStartGame(pIMessage mess);

    void TakeTimeStartToGame(pIMessage mess);
signals:



public slots:
    void SlotServerError(IMessage );
private:
    CEnterWindow * enterWindow;
};

#endif // GUI_H
