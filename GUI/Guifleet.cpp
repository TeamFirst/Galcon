#include <QVariant>
#include <QTransform>
#include <cmath>
#include "Guifleet.h"
#include "Guiplanet.h"

namespace GUI
{
   CGUIFleet::CGUIFleet(Game::CFleet* fleet):m_fleet(fleet)
   {
   }

   void CGUIFleet::Draw(QPainter* painter)
   {
      double d_x(0), d_y(0);
      m_fleet->GetPosition(d_x,d_y);
      int x(d_x), y(d_y);
      painter->setPen(Qt::white);
      painter->drawText(x - 15, y - 20,
               QVariant(quint32(m_fleet->GetShipCount())).toString());
      QPixmap image (":/SpaceshipSmall.png");
      QTransform tr;
      tr.rotateRadians(m_fleet->GetAngle());
      painter->drawPixmap(x - 22, y - 22, image.transformed(tr));
   }
} //Namespace GUI
