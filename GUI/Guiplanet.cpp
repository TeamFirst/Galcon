#include <QVariant>
#include <QRadialGradient>

#include "Guiplanet.h"

namespace GUI
{
   CGUIPlanet::CGUIPlanet(Game::CPlanet* planet)
      : m_planet(planet),
        m_active(false)
   {

   }

   void CGUIPlanet::Draw(QPainter* painter)
   {
      QBrush br(Qt::lightGray);
      unsigned x(0), y(0);
      m_planet->GetPosition(x,y);
      /// If planet is selected - draw a bit larger circle first
      painter->setPen(Qt::black);
      if(m_active)
      {
         painter->setBrush(Qt::blue);
         painter->drawEllipse(x - m_planet->GetRadius()/2 - 5, y - m_planet->GetRadius()/2 - 5,
                             m_planet->GetRadius() + 10, m_planet->GetRadius() + 10);
      }
      QRadialGradient gr(x, y, m_planet->GetRadius(), x, y);
      gr.setColorAt(0.0, Qt::white);
      gr.setColorAt(0.5, GetColor(m_planet->GetPlayerId()));
      gr.setColorAt(1.0, Qt::black);
      painter->setPen(Qt::NoPen);
      painter->setBrush(gr);
      painter->drawEllipse(x - m_planet->GetRadius()/2, y - m_planet->GetRadius()/2,
                          m_planet->GetRadius(), m_planet->GetRadius());
      /// Draw amount of army on planet
      painter->setPen(Qt::white);
      painter->drawText(x - m_planet->GetRadius()/2, y - m_planet->GetRadius()/2,
                        QVariant(quint32(m_planet->GetArmy())).toString());
   }

   void CGUIPlanet::MakeActive()
   {
      m_active = true;
   }

   void CGUIPlanet::ReleaseActive()
   {
      m_active = false;
   }

   bool CGUIPlanet::IsActive() const
   {
      return m_active;
   }

   Game::CPlanet* CGUIPlanet::GetPlanet() const
   {
      return m_planet;
   }

   QColor CGUIPlanet::GetColor(unsigned int id)
   {
      switch (id)
      {
         case 0:
            return Qt::gray;
            break;
         case 1:
            return Qt::red;
            break;
         case 2:
            return Qt::green;
            break;
         case 3:
            return Qt::blue;
            break;
         case 4:
            return QColor::fromRgb(0, 255,255);
            break;
         case 5:
            return QColor::fromRgb(255,0,255);
            break;
         case 6:
            return Qt::yellow;
            break;
         case 7:
            return QColor::fromRgb(96,0,0);
            break;
         case 8:
            return QColor::fromRgb(0, 96, 0);
            break;
         default:
            return Qt::lightGray;
            break;
      }
   }
} // Namespace GUI
