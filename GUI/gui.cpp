#include <QDialog>
#include <QDebug>
#include "gui.h"
#include "PlayWindow.h"
#include "WaitWindow.h"
#include "enterwindow.h"
#include "criticalmessage.h"
using namespace Message;
CGUI::CGUI(QObject *parent) :
    QObject(parent)
{
    m_connected = false;
    m_enterWindow = new CEnterWindow();
    m_waitWindow = new CWaitWindow();
    m_playWindow = new CPlayWindow();
    connect(m_enterWindow, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
            this, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)));


    connect(
                this, SIGNAL(sInConnectedToServer()),
                m_enterWindow, SLOT(slConnectedToServer())
            );

    connect(m_waitWindow, SIGNAL(sStarts()), this, SLOT(slGameStarts()));
}
void CGUI::Exec()
{
    m_enterWindow->exec();

}
void CGUI::TakeConfirmConnectToServer(CMessageConfirmationConnectToServerPtr mess)
{
    m_connected = true;
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
    if (m_connected)
    {
        static bool first = true;
        if (first )
        {
            m_waitWindow->show();
        }
        m_waitWindow->TakeStartGame(ptr);

        first = false;
    }
}
void CGUI::TakeError(Message::CMessageError mess)
{
    CCriticalMessage::Show("Error", "Error");
}
void CGUI::TakeFieldSize(unsigned int X, unsigned int Y)
{
    m_playWindow->TakeFieldSize(X, Y);
}
void CGUI::slGameStarts()
{
    qDebug() << "Game starts";
    m_waitWindow->hide();
    m_playWindow->show();
}
ISceneUpdates * CGUI::GetScene()
{
    if (!m_playWindow)
        return 0;
    return m_playWindow->GetView();
}
