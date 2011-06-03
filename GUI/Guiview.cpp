#include "Guiview.h"
#include <QVariant>
#include <QPainter>

CGUIView::CGUIView(unsigned int x, unsigned int y, QWidget* parent) :
   m_width(x),
   m_height(y),
   m_parent(parent)
{
   m_space = new CGUISpace(x,y);
}

CGUIView::~CGUIView()
{
}


void CGUIView::OnHideView()
{

}

void CGUIView::OnShowView()
{

}


void CGUIView::OnUpdate(const std::vector<CPlanet *>& planets, const std::list<CFleet *>& fleets)
{
   if (m_planets.empty())
   {
      for (unsigned int i = 0; i < planets.size(); ++i)
      {
         CGUIPlanet currPl(planets[i]);
         m_planets.push_back(currPl);
      }
   }
   m_fleets.erase(m_fleets.begin(), m_fleets.end());
   CFleet* iterfl;
   foreach( iterfl, fleets)
   {
      CGUIFleet currFl(iterfl);
      m_fleets.push_back(currFl);
   }
   m_parent->update();
}

void CGUIView::Draw(QPainter* painter)
{
   m_space->Draw(painter);
   painter->setBrush(Qt::green);
   CGUIPlanet currPl;
   foreach (currPl, m_planets)
   {
      currPl.Draw(painter);
   }
   CGUIFleet currFl;
   foreach(currFl, m_fleets)
   {
      currFl.Draw(painter);
   }


}
