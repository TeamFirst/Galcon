#include "Guiplanet.h"
#include <QVariant>

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
   if(m_active)
   {
      painter->setBrush(Qt::blue);
      painter->drawEllipse(x - m_planet->GetRadius()/2 - 5, y - m_planet->GetRadius()/2 - 5,
                          m_planet->GetRadius() + 10, m_planet->GetRadius() + 10);
   }   switch (m_planet->GetPlayerId())
   {
      case 0:
         br.setColor(Qt::gray);
         break;
      case 1:
         br.setColor(Qt::red);
         break;
      case 2:
         br.setColor(Qt::green);
         break;
      case 3:
         br.setColor(Qt::blue);
         break;
      case 4:
         br.setColor(QColor::fromRgb(0, 255,255));
         break;
      case 5:
         br.setColor(QColor::fromRgb(255,0,255));
         break;
      case 6:
         br.setColor(Qt::yellow);
         break;
      case 7:
         br.setColor(QColor::fromRgb(96,0,0));
         break;
      case 8:
         br.setColor(QColor::fromRgb(0, 96, 0));
         break;
      default:
         br.setColor(Qt::lightGray);
         break;

   }

   painter->setBrush(br);
   painter->drawEllipse(x - m_planet->GetRadius()/2, y - m_planet->GetRadius()/2,
                       m_planet->GetRadius(), m_planet->GetRadius());
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
