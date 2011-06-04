#pragma once

#include <QPainter>
#include <QColor>

#include "Game/Planet.h"

namespace GUI
{
   class CGUIPlanet
   {
   public:
      CGUIPlanet(){}
      CGUIPlanet(Game::CPlanet* planet);

      void Draw(QPainter*);

      Game::CPlanet* GetPlanet() const;

      void MakeActive();
      void ReleaseActive();
      bool IsActive() const;

      static QColor GetColor(unsigned int id);

   private:
      Game::CPlanet* m_planet;
      bool m_active;
   };
} // Namespace GUI
