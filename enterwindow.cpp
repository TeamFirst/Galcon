#include <QHostAddress>
#include <QVariant>
#include "enterwindow.h"
#include "ui_enterwindow.h"
#include "criticalmessage.h"

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

void CEnterWindow::on_connectButton_clicked()
{
    this->CheckAndSend();
}
void CEnterWindow::CheckAndSend()
{
    if (ui->m_ip->text() == "")
    {
        CCriticalMessage::Show("Error", "IP not entered");
        return;
    } else
        if (ui->m_port->text() == "")
        {
              CCriticalMessage::Show("Error", "Port not entered");
              return;
        } else
        if (ui->m_name->text() == "")
        {
            CCriticalMessage::Show("Error", "Name not entered");
            return;
        }
    QHostAddress host;
    if (!host.setAddress(ui->m_ip))
    {
        CCriticalMessage::Show("Error", "Bad IP");
        return;
    }
    if (!(QVariant(ui->m_port->text()).canConvert(QVariant::Int)))
    {
        CCriticalMessage::Show("Error", "Port is not valid");
        return;
    }
    emit SendClientToServer(
            QSharedPointer(
                    new CMessageConnectToServer(ui->m_name->text(), ui->m_ip->text(), QVariant(ui->m_port->text()).toInt())
                    )
            );
}
