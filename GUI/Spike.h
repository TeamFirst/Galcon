#ifndef SPIKE_H
#define SPIKE_H

#include <QObject>
#include <QTimer>
#include "gui.h"

#include "../message/MessageConnectToServer.h"
class CSpike : public QObject
{
    Q_OBJECT
public:
    explicit CSpike(QObject *parent = 0);

public slots:
    void slSendClientToServer(Message::CMessageConnectToServerPtr);

signals:
    void sConnectedToServer(Message::CMessageConfirmationConnectToServerPtr);
    void sGameStartsIn(Message::CMessageTimeToStartGamePtr ptr);

private slots:
    void slTimerSignal();
    void slSendStartGame();
    void slSendBoardSize();
private:
    CGUI gui;
    QTimer timer;

};

#endif // SPIKE_H
