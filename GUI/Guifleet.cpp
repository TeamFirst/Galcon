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

   void CGUIFleet::Draw(QPainter* painter, double scale)
   {
      const double PI = 3.141592653;
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
      tr.scale(0.5, 0.5);
      double angle = m_fleet->GetAngle();
      double diag = 27*sqrt(2);
      tr.rotateRadians(angle);
      if (abs(angle) > PI/2)
      {
         angle = angle > 0 ? angle - PI/2 : angle + PI/2;
      }


      if (angle > 0)
      {
         painter->drawPixmap(x - diag*sin(PI/4 + angle), y - diag*(cos(PI/4 - angle)), image.transformed(tr));
      }
      else
      {
         painter->drawPixmap(x - diag*sin(PI/4 - angle), y - diag*(cos(PI/4 + angle)), image.transformed(tr));
      }
   }
} //Namespace GUI
