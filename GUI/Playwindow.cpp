#include "Playwindow.h"
#include <QMouseEvent>

CPlayWindow::CPlayWindow(QWidget *parent):QWidget(parent)
{
}

void CPlayWindow::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   m_view->Draw(&painter);
   painter.setPen(Qt::blue);
   if(m_mouseSelection)
   {
      QLine l1(m_mousePressedX, m_mousePressedY, m_mousePressedX, m_mouseCurrentY);
      QLine l2(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mousePressedY);
      QLine l3(m_mousePressedX, m_mouseCurrentY, m_mouseCurrentX, m_mouseCurrentY);
      QLine l4(m_mouseCurrentX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY);
      QVector<QLine> lines;
      lines.push_back(l1);
      lines.push_back(l2);
      lines.push_back(l3);
      lines.push_back(l4);
      painter.drawLines(lines);
   }
}

void CPlayWindow::CreateWindow(const unsigned int x, const unsigned int y)
{
   m_view = new CGUIView(x, y, this);
   m_view->SetPlayerId(m_playerId);
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

void CPlayWindow::SetPlayerId(unsigned int id)
{
   m_playerId = id;
}

CGUIView* CPlayWindow::GetView()
{
   return m_view;
}

void CPlayWindow::mousePressEvent(QMouseEvent* event)
{
   m_mouseSelection = true;
   m_mousePressedX = event->pos().x();
   m_mousePressedY = event->pos().y();

   m_mouseActive = !m_mouseActive;
}

void CPlayWindow::mouseReleaseEvent(QMouseEvent* event)
{
   m_mouseSelection = false;
   m_mouseActive = !m_mouseActive;
   update();
}

void CPlayWindow::mouseMoveEvent(QMouseEvent* event)
{
   if (m_mouseSelection)
   {
      m_mouseCurrentX = event->pos().x();
      m_mouseCurrentY = event->pos().y();
      if(m_mouseActive)
      {
         m_view->Selection(m_mousePressedX, m_mousePressedY,
                        m_mouseCurrentX, m_mouseCurrentY);
      }
      update();
   }

}

void CPlayWindow::wheelEvent(QWheelEvent* event)
{
   int numDegrees = event->delta() / 8;
   int numSteps = numDegrees / 15;
   m_view->SetPercent(m_view->GetPercent() + numSteps);
   update();
}


