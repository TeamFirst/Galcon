#include <QHostAddress>
#include "enterwindow.h"
#include "ui_enterwindow.h"
#include "criticalmessage.h"

CEnterWindow::CEnterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEnterWindow)
{
    ui->setupUi(this);
}

CEnterWindow::~CEnterWindow()
{
    delete ui;
}

void CEnterWindow::on_connectButton_clicked()
{
    this->CheckAndSend();
}
void CEnterWindow::CheckAndSend()
{
    if (ui->m_ip->text() == "")
    {
        CCriticalMessage::Show("Error", "IP not entered");
    } else
        if (ui->m_port->text() == "")
        {
        CCriticalMessage::Show("Error", "Port not entered");
    } else
        if (ui->m_name->text() == "")
        {
        CCriticalMessage::Show("Error", "Name not entered");
    }
    QHostAddress host;



}
