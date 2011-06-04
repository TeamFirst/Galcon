#include "Guiview.h"
#include <QVariant>
#include <QPainter>

CGUIView::CGUIView(unsigned int x, unsigned int y, QWidget* parent) :
   m_width(x),
   m_height(y),
   m_parent(parent),
   m_percent(50)
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
         CGUIPlanet* currPl = new CGUIPlanet(planets[i]);
         m_planets.push_back(currPl);
      }
   }
   m_fleets.erase(m_fleets.begin(), m_fleets.end());
   CFleet* iterfl;
   foreach( iterfl, fleets)
   {
      CGUIFleet* currFl = new CGUIFleet(iterfl);
      m_fleets.push_back(currFl);
   }
   m_parent->update();
}

void CGUIView::Draw(QPainter* painter)
{
   painter->setBrush(Qt::green);
   m_space->Draw(painter);
   CGUIPlanet* currPl;
   foreach (currPl, m_planets)
   {
      currPl->Draw(painter);
   }
   CGUIFleet* currFl;
   foreach(currFl, m_fleets)
   {
      currFl->Draw(painter);
   }
}

void CGUIView::Selection(unsigned int beginX, unsigned int beginY,
                         unsigned int endX, unsigned int endY)
{
   CGUIPlanet* currPl;
   unsigned int x(0), y(0);
   foreach(currPl, m_planets)
   {
      CPlanet* pl = currPl->GetPlanet();
      pl->GetPosition(x,y);
      if ((x >= std::min(beginX, endX)) && (x <= std::max(beginX, endX))
            && (y >= std::min(beginY, endY)) && (y <= std::max(beginY,endY)))
      {
         currPl->MakeActive();
      }
      else
      {
         currPl->ReleaseActive();
      }
   }
}
