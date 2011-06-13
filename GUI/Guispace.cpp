#include "Guispace.h"

namespace GUI
{
   CGUISpace::CGUISpace(unsigned int x, unsigned int y):m_width(x), m_height(y)
   {
   }

   void CGUISpace::Draw(QPainter* painter)
   {
      painter->setBrush(Qt::black);
      painter->drawRect(0, 0, m_width, m_height);

      QPixmap pm(":/GUI/backspace.png");
      painter->drawPixmap(0,0, pm);
   }
} // Namespace GUI
