#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include "ui_playwindow.h"
#include "message/MessageStartMapGame.h"
#include "PlayWindow.h"

#include "PlayArea.h"
#include "GUIPlanet.h"
#include "GUIFleet.h"
#include "../Planet.h"
#include "../Fleet.h"
#include "GUISky.h"
#include <QHBoxLayout>
CPlayWindow::CPlayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPlayWindow)
{
    m_playArea = 0;
    ui->setupUi(this);
    lay = new QHBoxLayout(this);
    this->setLayout(lay);
}

CPlayWindow::~CPlayWindow()
{
    delete ui;
}
void CPlayWindow::TakeFieldSize(unsigned int X, unsigned int Y)
{
    m_verLogic = Y;
    m_horLogic = X;

    m_playArea = new TView(this);

    lay->addWidget(m_playArea);

    m_playArea->resize(this->size().width() * 0.9, size().height() * 0.9);

    SetNewPlaySize();

    m_playArea->setScene(&m_scene);

    m_playArea->setBackgroundBrush(Qt::black);
    m_scene.addItem(new CGUISky());


    DrawSky();
    connect(&m_view, SIGNAL(sUpdate()), this, SLOT(slUpdate()));
    emit SendScene(&m_view);
}
void CPlayWindow::SetNewPlaySize()
{
    m_horPhys = m_playArea->size().width();
    m_verPhys = m_playArea->size().height();

    double kX = m_horPhys / m_horLogic;
    double kY =  m_verPhys / m_verLogic;

    m_k = kX < kY ? kX : kY;

    m_playArea->resize(m_horPhys * m_k, m_verPhys * m_k);

    m_horPhys = m_playArea->size().width();
    m_verPhys = m_playArea->size().height();
}
void CPlayWindow::slGameStarts()
{
    m_planets = m_view.GetPlanets();
    m_fleets = m_view.GetFleets();
    for (unsigned int i = 0; i < m_planets->size(); i++)
    {
        m_scene.addItem(new CGUIPlanet((*m_planets)[i], &m_k, this));
    }
}
CGUIView * CPlayWindow::GetView()
{
    return &m_view;
}
void CPlayWindow::UpdateFleets()
{
    m_scene.clear();
    std::list<CFleet* >::const_iterator it;
    CGUIFleet * fl;
    it = m_fleets->begin();
    for (; it !=  (*m_fleets).end(); it++)
    {

        for (int i = 0; i < m_gFleets.size(); i++)
        {
            if (((*it)->GetId()) == ((m_gFleets)[i])->GetFleet()->GetId())
            {
                goto out;
            }
        }
        fl = new CGUIFleet((*it), &m_k, this);
        m_scene.addItem(fl);
        m_gFleets.push_back(fl);

        out:
            int c = 0;
    }
}
void CPlayWindow::slUpdate()
{
    UpdateFleets();
    m_playArea->repaint();


}
void CPlayWindow::DrawSky()
{
    QPixmap pixmap(":/GUI/sky.png");



    m_scene.addPixmap(pixmap);

    m_playArea->repaint();
}
