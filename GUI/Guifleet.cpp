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
      double PI = 3.141592653;
      m_fleet->GetPosition(d_x,d_y);
      int x(d_x), y(d_y);
      painter->setPen(Qt::white);
      painter->drawText(x - 15, y - 20,
               QVariant(quint32(m_fleet->GetShipCount())).toString());

      /// Drawing image

      QPixmap image (":/SpaceshipSmall.png");
      QTransform tr;

      /// Rotate on right angle

      double angle = m_fleet->GetAngle();
      tr.rotateRadians(angle);

      /// Shift image to center it

//      unsigned int image_w = 55;
//      unsigned int image_h = 55;
//      int offset_x(0), offset_y(0);
//      if ((angle < PI/4) && (angle > -PI/4))
//      {
//         offset_x = -image_w/2;
//         offset_y = -image_h/2;
//      }
//      else if ((angle >= PI/4) && (angle < 3*PI/4))
//      {
//         offset_x = image_w/2;
//         offset_y = -image_h/2;
//      }
//      else if ((angle >= 3*PI/4 ) || (angle < -3*PI/4))
//      {
//         offset_x = image_w/2;
//         offset_y = image_h/2;
//      }
//      else
//      {
//         offset_x = -image_w/2;
//         offset_y = image_h/2;
//      }

      painter->drawPixmap(x - 27, y - 27, image.transformed(tr));
   }
} //Namespace GUI
