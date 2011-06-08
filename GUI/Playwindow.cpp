#include "Playwindow.h"
#include "Guiview.h"
#include <QMouseEvent>
#include <QLine>
#include <QVector>
#include <QPainter>

namespace GUI
{
   CPlayWindow::CPlayWindow(QWidget *parent) :
      QWidget(parent),
      m_mouseState(ENotSelected),
      m_mouseClick(ENone),
      m_mouseRelease(true),
      m_mousePressedX(0),
      m_mousePressedY(0),
      m_mouseCurrentX(0),
      m_mouseCurrentY(0),
      m_width(1000),
      m_height(800)
   {
   }

   void CPlayWindow::CreateWindow(const unsigned int x, const unsigned int y)
   {
      m_logicalWidth = x;
      m_logicalHeight = y;
      m_view = new CGUIView(x, y, this);
      m_view->SetPlayerId(m_playerId);
      resize(m_width, m_height);
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

   void CPlayWindow::paintEvent(QPaintEvent *)
   {
      QPainter painter(this);
      painter.setWindow(0, 0, m_logicalWidth, m_logicalHeight);
      painter.setViewport(0, 0, m_width, m_height);
      m_view->Draw(&painter);

      /// Draw mouse selection rectangle

      painter.setPen(Qt::blue);
      if (!m_mouseRelease)
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

   void CPlayWindow::SetPlayerId(unsigned int id)
   {
      m_playerId = id;
   }

   CGUIView* CPlayWindow::GetView()
   {
      return m_view;
   }

   void CPlayWindow::GetSize(unsigned int &width, unsigned int &height)
   {
      width = m_width;
      height = m_height;
   }

   void CPlayWindow::GetLogicalFromActual(int &x, int &y) const
   {
      x *= (double)m_logicalWidth/m_width;
      y *= (double)m_logicalHeight/m_height;
   }

   void CPlayWindow::mousePressEvent(QMouseEvent* event)
      {
         m_mouseClick = ESingle;
         m_mouseRelease = false;
         m_mousePressedX = event->pos().x();
         m_mousePressedY = event->pos().y();
         m_mouseCurrentX = event->pos().x();
         m_mouseCurrentY = event->pos().y();
         GetLogicalFromActual(m_mousePressedX, m_mousePressedY);
         GetLogicalFromActual(m_mouseCurrentX, m_mouseCurrentY);
      }

   void CPlayWindow::mouseDoubleClickEvent(QMouseEvent* event)
   {
      m_mouseClick = EDouble;
      m_mouseRelease = false;
      m_mousePressedX = event->pos().x();
      m_mousePressedY = event->pos().y();
      GetLogicalFromActual(m_mousePressedX, m_mousePressedY);
   }

   void CPlayWindow::mouseReleaseEvent(QMouseEvent* event)
   {
      m_mouseRelease = true;
      m_mouseCurrentX = event->pos().x();
      m_mouseCurrentY = event->pos().y();
      GetLogicalFromActual(m_mouseCurrentX, m_mouseCurrentY);
      if (m_mouseClick == ESingle)
      {
         if ((m_mousePressedX == m_mouseCurrentX) &&
               (m_mousePressedY == m_mouseCurrentY))
         {
            if (m_mouseState == EPlanetsSelected)
            {
               Message::CMessageStepPlayerPtr mess = m_view->Target(m_mousePressedX, m_mousePressedY);
               if (mess->m_percent != 0 && !mess->m_startPlanetID.empty())
               {
                  emit SendStepPlayer(mess);
               }

               m_view->Selection(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY);
               m_mouseState = ENotSelected;
            }
            else
            {
               if (m_view->SelectOne(m_mousePressedX, m_mousePressedY))
               {
                  m_mouseState = EPlanetsSelected;
               }
               else
               {
                  m_mouseState = ENotSelected;
               }
            }
         }
         else
         {
            if (m_view->Selection(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY))
            {
               m_mouseState = EPlanetsSelected;
            }
            else
            {
               m_mouseState = ENotSelected;
            }
         }
      }
      else if (m_mouseClick == EDouble)
      {
         if (m_mouseState == EPlanetsSelected &&
               ((m_mousePressedX != m_mouseCurrentX) || (m_mousePressedY != m_mouseCurrentY)))
         {
            Message::CMessageStepPlayerPtr mess = m_view->Target(m_mousePressedX, m_mousePressedY);
            if (mess->m_percent != 0 && !mess->m_startPlanetID.empty())
            {
               emit SendStepPlayer(mess);
            }
            m_view->Selection(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY);
            m_mouseState = ENotSelected;
         }
         else
         {
            m_view->CheckAll(m_mouseCurrentX, m_mouseCurrentY);
            m_mouseState = EPlanetsSelected;
         }
      }
      else
      {
         //Bug
      }
      m_mouseClick = ENone;
      update();
   }

   void CPlayWindow::mouseMoveEvent(QMouseEvent* event)
   {
      if (m_mouseClick == ESingle && !m_mouseRelease)
      {
         m_mouseCurrentX = event->pos().x();
         m_mouseCurrentY = event->pos().y();
         GetLogicalFromActual(m_mouseCurrentX, m_mouseCurrentY);
         m_view->Selection(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY);
         update();
      }
      else if (m_mouseClick == ENone)
      {
         //to do later
      }
   }

   void CPlayWindow::wheelEvent(QWheelEvent* event)
   {
      int numDegrees = event->delta() / 8;
      int numSteps = numDegrees / 15;
      m_view->SetPercent(m_view->GetPercent() + numSteps);
      update();
   }

   void CPlayWindow::resizeEvent(QResizeEvent* event)
   {
      QSize newsize = event->size();
      if ((newsize.width() != m_width) || (newsize.height() != m_height))
      {
         resize(m_width, m_height);
      }
//      if ((double)newsize.width()/newsize.height() > (double)m_logicalWidth/m_logicalHeight)
//      {
//         resize(newsize.width(), (double)(newsize.width()/m_logicalWidth) * m_logicalHeight);
//      }
//      {
//         resize(((double)(newsize.height()/m_logicalHeight) * m_logicalWidth), newsize.height());
//      }
   }
} //Namespace GUI

