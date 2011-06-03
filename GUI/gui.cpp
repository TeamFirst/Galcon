#include <QDialog>
#include <QDebug>
#include "gui.h"
#include "PlayWindow.h"
#include "WaitWindow.h"
#include "enterwindow.h"
#include "criticalmessage.h"

CGUI::CGUI(QObject *parent) :
   QObject(parent),
   m_playerId(0)
{
    m_enterWindow = new CEnterWindow();
    m_waitWindow = new CWaitWindow();
    m_playWindow = new CPlayWindow();

    connect(m_enterWindow, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)),
            this, SIGNAL(SendClientToServer(Message::CMessageConnectToServerPtr)));
}

CGUI::~CGUI()
{
   delete m_enterWindow;
   delete m_waitWindow;
   delete m_playWindow;
}

void CGUI::ShowWindow()
{
   m_enterWindow->ShowWindow();
}

void CGUI::HideWindow()
{
   m_enterWindow->HideWindow();
}

void CGUI::TakeConfirmConnectToServer(Message::CMessageConfirmationConnectToServerPtr mess)
{
    m_playerId = mess->m_playerID;

    m_enterWindow->HideWindow();
    m_waitWindow->ShowWindow();
}

void CGUI::TakeError(Message::CMessageErrorPtr mess)
{
   CCriticalMessage::Show("Server error", mess->m_strError.c_str());
}

void CGUI::TakeTimeStartToGame(Message::CMessageTimeToStartGamePtr mess)
{
   m_waitWindow->SetSecondToStart(mess->m_second);
}

void CGUI::TakeFinishGame(Message::CMessageFinishGamePtr mess)
{
}


void CGUI::TakeInError(std::string mess)
{
   CCriticalMessage::Show("Inside program error", mess.c_str());
}

void CGUI::TakeStartGame(Message::CMessageTimeToStartGamePtr ptr)
{   
}


void CGUI::TakeFieldSize(unsigned int X, unsigned int Y)
{    
}

