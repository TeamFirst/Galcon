#include <QDialog>
#include <QDebug>
#include "gui.h"
#include "Playwindow.h"
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
    connect(m_playWindow, SIGNAL(SendStepPlayer(Message::CMessageStepPlayerPtr)),
            this, SIGNAL(SendStepPlayer(Message::CMessageStepPlayerPtr)));
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

void CGUI::DestroyWindow()
{
   m_enterWindow->DestroyWindow();
}

void CGUI::TakeConfirmConnectToServer(const Message::CMessageConfirmationConnectToServerPtr mess)
{
    m_playerId = mess->m_playerID;

    m_enterWindow->DestroyWindow();
    m_waitWindow->ShowWindow();
}

void CGUI::TakeError(const Message::CMessageErrorPtr mess)
{
   CCriticalMessage::Show("Server error", mess->m_strError.c_str());
}

void CGUI::TakeTimeStartToGame(const Message::CMessageTimeToStartGamePtr mess)
{
   m_waitWindow->SetSecToStart(mess->m_second);
}

void CGUI::TakeFinishGame(const Message::CMessageFinishGamePtr mess)
{
   m_playWindow->DestroyWindow();
   m_enterWindow->ShowWindow();
}

void CGUI::TakeInInformation(const Message::CMessageInformationPtr mess)
{
   //CCriticalMessage::Show("Inside program error", mess->m_strInformation.c_str());
}

void CGUI::TakeFieldSize(const unsigned int X, const unsigned int Y)
{
   m_playWindow->SetPlayerId(m_playerId);
   m_playWindow->CreateWindow(X, Y);
   m_waitWindow->DestroyWindow();
   m_playWindow->ShowWindow();

   Message::CMessageAddViewPtr ptr(new Message::CMessageAddView);
   ptr->m_view = m_playWindow->GetView();
   SendView(ptr);
}

