#include "Playwindow.h"

CPlayWindow::CPlayWindow(QWidget *parent):QWidget(parent)
{
}

void CPlayWindow::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   m_view->Draw(&painter);
}

void CPlayWindow::setView(CGUIView *view)
{
   m_view = view;
}

ISceneUpdates* CPlayWindow::GetView() const
{
   qDebug("Trying to cast");
   return m_view;
}

void CPlayWindow::CreateWindow(unsigned int x, unsigned int y)
{
   qDebug("Creating window");
   m_view = new CGUIView(x,y,this);
}

void CPlayWindow::ShowWindow()
{
   show();
}

void CPlayWindow::DestroyWindow()
{
   hide();
}

