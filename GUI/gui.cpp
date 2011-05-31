#include <QDialog>
#include <QDebug>
#include "gui.h"
#include "WaitWindow.h"
using namespace Message;
CGUI::CGUI(QObject *parent) :
    QObject(parent)
{
    m_enterWindow = new CEnterWindow();
    m_waitWindow = new CWaitWindow();
    connect(m_enterWindow, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
            this, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)));

    //connect(m_enterWindow, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
    //        this, SLOT(slSendClientToServer(Message::CMessageConnectToServerPtr)));

    connect(
                this, SIGNAL(sInConnectedToServer()),
                m_enterWindow, SLOT(slConnectedToServer())
            );
}
void CGUI::Exec()
{
    m_enterWindow->exec();

}
void CGUI::TakeConfirmConnectToServer(CMessageConfirmationConnectToServerPtr mess)
{
    this->m_playerId = mess->m_playerID;
    //emit sInConnectedToServer();
    m_enterWindow->slConnectedToServer();

}
CGUI::~CGUI()
{
    m_enterWindow->deleteLater();
}

void CGUI::TakeStartGame(Message::CMessageTimeToStartGamePtr ptr)
{
    static bool first = true;
    if (first )
    {
        m_waitWindow->show();;
    }
    m_waitWindow->TakeStartGame(ptr);
    first = false;
}
