#include <QTimer>
#include "WaitWindow.h"
#include "ui_waitwindow.h"

CWaitWindow::CWaitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CWaitWindow)
{
    ui->setupUi(this);
    m_timer.setInterval(1000);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slTimer()));
}

CWaitWindow::~CWaitWindow()
{
    delete ui;
}
void CWaitWindow::TakeStartGame(Message::CMessageTimeToStartGamePtr ptr)
{

    this->m_left = ptr->m_second;
    int left = m_left;
    ui->lcdNumber->display(left);
    m_timer.start();
}

void CWaitWindow::slTimer()
{
    m_left--;

    ui->lcdNumber->display((int)m_left);
    if (!m_left)
    {
        m_timer.stop();
    }
}
