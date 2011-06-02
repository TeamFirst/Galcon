#ifndef GUI_H
#define GUI_H

#include <QObject>



#include "message/MessageConnectToServer.h"
#include "message/MessageTimeToStartGame.h"
#include "message/MessageStartMapGame.h"
#include "message/MessageError.h"
class CPlayWindow;
class CWaitWindow;
class CEnterWindow;
class ISceneUpdates;
class CGUI : public QObject
{
    Q_OBJECT
public:
    explicit CGUI(QObject *parent = 0);
    ISceneUpdates * GetScene();
    virtual ~CGUI();

    void Exec();


public slots:

    void TakeError(Message::CMessageErrorPtr mess);

//    void TakeFinishGame(pIMessage mess);

    void TakeFieldSize(unsigned int X, unsigned int Y);

//    void TakeTimeStartToGame(pIMessage mess);
    void TakeStartGame(Message::CMessageTimeToStartGamePtr ptr);

    void TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr mess);

signals:
    void SendClientToServer(Message::CMessageConnectToServerPtr mess);

    void sInConnectedToServer();


private slots:
    //void SlotServerError(IMessage );
    //void slSendClientToServer(Message::CMessageConnectToServerPtr mess);
    void slGameStarts();
private:
    bool m_connected;
    int m_playerId;
    CWaitWindow * m_waitWindow;
    CEnterWindow * m_enterWindow;
    CPlayWindow * m_playWindow;
};

#endif // GUI_H
