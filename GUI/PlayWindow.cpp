#include "PlayWindow.h"
#include "ui_playwindow.h"
#include "message/MessageStartMapGame.h"
CPlayWindow::CPlayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPlayWindow)
{
    ui->setupUi(this);
}

CPlayWindow::~CPlayWindow()
{
    delete ui;
}
void CPlayWindow::TakeStartGame(Message::CMessageStartMapGamePtr mess)
{
    m_verLogic = mess->m_mapY;
    m_horLogic = mess->m_mapX;

    SetNewPlaySize();



}
void CPlayWindow::SetNewPlaySize()
{
    m_horPhys = ui->m_play->size().width();
    m_verPhys = ui->m_play->size().height();

    double kX = m_horPhys / m_horLogic;
    double kY =  m_verPhys / m_verLogic;

    m_k = kX < kY ? kX : kY;

    ui->m_play->resize(m_horPhys * m_k, m_verPhys * m_k);

    m_horPhys = ui->m_play->size().width();
    m_verPhys = ui->m_play->size().height();
}
