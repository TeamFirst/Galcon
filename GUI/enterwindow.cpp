#include <QHostAddress>
#include <QVariant>
#include "enterwindow.h"
#include "ui_enterwindow.h"
#include "criticalmessage.h"
using namespace Message;
CEnterWindow::CEnterWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CEnterWindow)
{
    ui->setupUi(this);
}

CEnterWindow::~CEnterWindow()
{
    delete ui;
}

void CEnterWindow::ShowWindow()
{
   show();
}

void CEnterWindow::DestroyWindow()
{
   hide();
}

void CEnterWindow::on_connectButton_clicked()
{
    CheckAndSend();
}

void CEnterWindow::CheckAndSend()
{
   if (ui->m_ip->text() == "")
   {
       CCriticalMessage::Show("Error", "IP not entered");
       return;
   }
   else if (ui->m_port->text() == "")
   {
      CCriticalMessage::Show("Error", "Port not entered");
      return;
   }
   else if (ui->m_name->text() == "")
   {
      CCriticalMessage::Show("Error", "Name not entered");
      return;
   }
   QHostAddress host;
   if (!host.setAddress(ui->m_ip->text()))
   {
      CCriticalMessage::Show("Error", "Bad IP");
      return;
   }
   if (!(QVariant(ui->m_port->text()).canConvert(QVariant::Int)))
   {
      CCriticalMessage::Show("Error", "Port is not valid");
      return;
   }
   CMessageConnectToServerPtr pcm(new CMessageConnectToServer());
   pcm->m_namePlayer = ui->m_name->text().toStdString();
   pcm->m_serverIP = ui->m_ip->text().toStdString();
   pcm->m_serverPort = ui->m_port->text().toInt();
   emit SendClientToServer(pcm);
}

