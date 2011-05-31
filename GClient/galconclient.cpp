#include "galconclient.h"
#include "ui_galconclient.h"

#include <QtNetwork>

#include "message/MessageConnectToServer.h"

CGalconClient::CGalconClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGalconClient)
{
    ui->setupUi(this);
}

CGalconClient::~CGalconClient()
{
    delete ui;
}

void CGalconClient::on_pBServerManager_clicked()
{
   Message::CMessageConnectToServerPtr pMes(new Message::CMessageConnectToServer);
   (*pMes).m_namePlayer = "GrafAllukard";
   (*pMes).m_serverIP = "127.0.0.1";
   (*pMes).m_serverPort = 1234;

   m_serverManager.TakeServerConnect(pMes);
}

void CGalconClient::on_pBSend_clicked()
{

}
