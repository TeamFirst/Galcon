#include <QVariant>
#include "Guifleet.h"
#include "Guiplanet.h"

namespace GUI
{
   CGUIFleet::CGUIFleet(Game::CFleet* fleet):m_fleet(fleet)
   {
   }

   void CGUIFleet::Draw(QPainter* painter)
   {
      double d_x(0), d_y(0), fX(0), fY(0);
      m_fleet->GetPosition(d_x,d_y);
      m_fleet->GetFixedPoint(fX,fY);
      int x(d_x), y(d_y);
      int fixX(fX), fixY(fY);
      painter->setBrush(CGUIPlanet::GetColor(m_fleet->GetPlayerId()));
      painter->setPen(Qt::white);
      painter->drawEllipse(x - 5, y - 5, 10 ,10);
      painter->drawLine(x,y, fixX, fixY);
      painter->setBrush(CGUIPlanet::GetColor(m_fleet->GetPlayerId()));
      painter->drawEllipse(fixX - 5, fixY - 5, 10 ,10);
      painter->drawText(x - 5, y - 10,
               QVariant(quint32(m_fleet->GetShipCount())).toString());

   }
} //Namespace GUI
