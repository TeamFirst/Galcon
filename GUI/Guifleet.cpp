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

      /// Determine fleets position

      double d_x(0), d_y(0);
      m_fleet->GetPosition(d_x,d_y);
      int x(d_x), y(d_y);

      /// Draw text upon the fleet

      painter->setPen(Qt::white);
      painter->drawText(x - 15, y - 20,
               QVariant(quint32(m_fleet->GetShipCount())).toString());

      /// Determine right image file, depends on fleet's owner

      QString imageSource;
      imageSource.setNum(m_fleet->GetPlayerId());
      imageSource = ":/SpaceshipSmall" + imageSource + ".png";
      QPixmap image (imageSource);

      /// Rotate on right angle

      QTransform tr;
      double angle = m_fleet->GetAngle();
      tr.rotateRadians(angle);

      painter->drawPixmap(x - 37, y - 37, image.transformed(tr));
   }
} //Namespace GUI
