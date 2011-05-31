#include "Spike.h"
#include <QDebug>
CSpike::CSpike(QObject *parent) :
    QObject(parent)
{    

    bool res;
    res = QObject::connect(
                this, SIGNAL(sConnectedToServer(Message::CMessageConfirmationConnectToServerPtr)),
                &gui, SLOT(TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr))
                );

    res = QObject::connect(&gui, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
                     this, SLOT(slSendClientToServer(Message::CMessageConnectToServerPtr))
                     );
    QObject::connect(this, SIGNAL(sGameStartsIn(Message::CMessageTimeToStartGamePtr)),
                     &gui, SLOT(TakeStartGame(Message::CMessageTimeToStartGamePtr)));
    gui.Exec();

}
void CSpike::slSendClientToServer(Message::CMessageConnectToServerPtr ptr)
{
    qDebug() << "Client has send data for connection";
//    timer.start(5000);
//    connect(&timer, SIGNAL(timeout()), this, SLOT(slTimerSignal()));
    timer.singleShot(2000, this, SLOT(slTimerSignal()));
}

void CSpike::slTimerSignal()
{
    qDebug() << "Timer immitates server connected signal";
    Message::CMessageConfirmationConnectToServerPtr ptr(new Message::CMessageConfirmationConnectToServer());
    ptr->m_playerID = 8;
    qDebug() << "Id user set to 8";
    timer.singleShot(2000, this, SLOT(slSendStartGame()));
    this->gui.TakeConfirmConnectToServer(ptr);
}
void CSpike::slSendStartGame()
{
    Message::CMessageTimeToStartGamePtr ptr(new Message::CMessageTimeToStartGame());
    ptr->m_second = 10;
    emit sGameStartsIn(ptr);
}
