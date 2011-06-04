#pragma once

#include <QPainter>
#include "Game/Fleet.h"

namespace GUI
{
   class CGUIFleet
   {
   public:
       CGUIFleet(){};
       CGUIFleet(Game::CFleet*);

       void Draw(QPainter*);

   private:
       Game::CFleet* m_fleet;
   };
} // Namespace GUI
