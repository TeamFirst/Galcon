#include "Playwindow.h"
#include "Guiview.h"
#include <QMouseEvent>
#include <QLine>
#include <QVector>
#include <QPainter>

namespace GUI
{
   CPlayWindow::CPlayWindow(QWidget *parent) : QWidget(parent)
   {
   }

   void CPlayWindow::CreateWindow(const unsigned int x, const unsigned int y)
   {
      m_view = new CGUIView(x, y, this);
      m_view->SetPlayerId(m_playerId);
      resize(x,y);
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

      m_view->Draw(&painter);

      // Draw mouse selection rectangle
      painter.setPen(Qt::blue);
      if (!m_mouseRelease && !m_mousePlanetState)
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

   void CPlayWindow::mousePressEvent(QMouseEvent* event)
      {
         m_mouseClick = ESingle;
         m_mouseRelease = false;
         m_mousePressedX = event->pos().x();
         m_mousePressedY = event->pos().y();
      }

   void CPlayWindow::mouseDoubleClickEvent(QMouseEvent* event)
   {
      m_mouseClick = EDouble;
      m_mouseRelease = false;
      m_mousePressedX = event->pos().x();
      m_mousePressedY = event->pos().y();
   }

   void CPlayWindow::mouseReleaseEvent(QMouseEvent* event)
   {
      m_mouseRelease = true;
      m_mouseCurrentX = event->pos().x();
      m_mouseCurrentY = event->pos().y();

      if (m_mouseClick == ESingle)
      {
         if ((m_mousePressedX == event->pos().x()) &&
               (m_mousePressedY == event->pos().y()))
         {
            if (m_mousePlanetState)
            {
               Message::CMessageStepPlayerPtr mess = m_view->Target(m_mousePressedX, m_mousePressedY);
               if (mess->m_percent != 0 && !mess->m_startPlanetID.empty())
               {
                  emit SendStepPlayer(mess);
               }
               m_view->Selection(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY);
               m_mousePlanetState = false;
            }
            else
            {
               if (m_view->Selection(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY))
               {
                  m_mousePlanetState = true;
               }
               else
               {
                  m_mousePlanetState = false;
               }
            }
         }
         else
         {
            if (m_view->Selection(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY))
            {
               m_mousePlanetState = true;
            }
            else
            {
               m_mousePlanetState = false;
            }
         }
      }
      else if (m_mouseClick == EDouble)
      {
         if (m_mousePlanetState)
         {
            Message::CMessageStepPlayerPtr mess = m_view->Target(m_mousePressedX, m_mousePressedY);
            if (mess->m_percent != 0 && !mess->m_startPlanetID.empty())
            {
               emit SendStepPlayer(mess);
            }
            m_view->Selection(m_mousePressedX, m_mousePressedY, m_mouseCurrentX, m_mouseCurrentY);
            m_mousePlanetState = false;
         }
         else
         {
            m_view->CheckAll(event->pos().x(), event->pos().y());
            m_mousePlanetState = true;
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
} //Namespace GUI

