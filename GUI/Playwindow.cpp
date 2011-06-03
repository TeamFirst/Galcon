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

void CPlayWindow::ShowWindow()
{
   show();
}

void CPlayWindow::DestroyWindow()
{
   hide();
}

