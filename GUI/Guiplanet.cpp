#include "Guiplanet.h"
#include <QVariant>

CGUIPlanet::CGUIPlanet(CPlanet* planet)
   : m_planet(planet),
     is_active(false)
{

}

void CGUIPlanet::Draw(QPainter* painter)
{
   QBrush br(Qt::lightGray);
   unsigned x(0), y(0);
   m_planet->GetPosition(x,y);
   switch (m_planet->GetPlayerId())
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
