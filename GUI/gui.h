#ifndef GUI_H
#define GUI_H

#include <QObject>
#include "WaitWindow.h"

#include "enterwindow.h"
#include "message/MessageConnectToServer.h"
#include "message/MessageTimeToStartGame.h"
#include "message/MessageStartMapGame.h"
#include "PlayWindow.h"
class CGUI : public QObject
{
    Q_OBJECT
public:
    explicit CGUI(QObject *parent = 0);
    virtual ~CGUI();

    void Exec();

public slots:

    //void TakeError(pIMessage mess);
    //void TakeFinishGame(pIMessage mess);
    //void TakeTimeStartToGame(pIMessage mess);
    void TakeStartGame(Message::CMessageTimeToStartGamePtr ptr);

    void TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr mess);

signals:
    void SendClientToServer(Message::CMessageConnectToServerPtr mess);

    void sInConnectedToServer();

private slots:
    //void SlotServerError(IMessage );
    //void slSendClientToServer(Message::CMessageConnectToServerPtr mess);

private:
    int m_playerId;
    CWaitWindow * m_waitWindow;
    CEnterWindow * m_enterWindow;
    CPlayWindow * m_playWindow;
};

#endif // GUI_H
