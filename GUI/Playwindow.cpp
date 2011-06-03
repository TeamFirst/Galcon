#include "Playwindow.h"

CPlayWindow::CPlayWindow(QWidget *parent):QWidget(parent)
{
}

void CPlayWindow::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   m_view->Draw(&painter);
}

void CPlayWindow::CreateWindow(const unsigned int x, const unsigned int y)
{
   m_view = new CGUIView(x, y, this);
}

void CPlayWindow::ShowWindow()
{
   show();
}

void CPlayWindow::DestroyWindow()
{
   hide();
   delete m_view;
}

CGUIView* CPlayWindow::GetView()
{
   return m_view;
}

