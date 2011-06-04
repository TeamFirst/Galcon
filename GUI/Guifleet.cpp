#include "Guifleet.h"

CGUIFleet::CGUIFleet(Game::CFleet* fleet):m_fleet(fleet)
{

}

void CGUIFleet::Draw(QPainter* painter)
{
   double d_x(0), d_y(0);
   m_fleet->GetPosition(d_x,d_y);
   unsigned int x(d_x), y(d_y);
   painter->drawEllipse(x - 10, y - 10, 20 ,20);
}
