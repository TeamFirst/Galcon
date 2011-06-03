#include <QTimer>
#include "WaitWindow.h"
#include "ui_waitwindow.h"

CWaitWindow::CWaitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CWaitWindow)
{
    ui->setupUi(this);
    m_timer.setInterval(1000);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotIncremetTimer()));
}

CWaitWindow::~CWaitWindow()
{
    delete ui;
}

void CWaitWindow::ShowWindow()
{
   show();
}

void CWaitWindow::HideWindow()
{
   m_timer.stop();
   ui->lcdNumber->hide();
   hide();
}

void CWaitWindow::SetSecondToStart(unsigned int second)
{
   m_secondToStart = second;
   ui->lcdNumber->display((int)m_secondToStart);
   m_timer.start();
}

void CWaitWindow::slotIncremetTimer()
{
    --m_secondToStart;

    ui->lcdNumber->display((int)m_secondToStart);
    if (!m_secondToStart)
    {
        m_timer.stop();
    }
}
