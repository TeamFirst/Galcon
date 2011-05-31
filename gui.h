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

    void Take
signals:
    void SendClientToServer(pIMessage mess);


public slots:
    void SlotServerError(IMessage );
private:
    CEnterWindow * m_enterWindow;
};

#endif // GUI_H
