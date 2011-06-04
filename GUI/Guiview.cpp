#include "Guiview.h"
#include <QVariant>
#include <QPainter>

CGUIView::CGUIView(unsigned int x, unsigned int y, QWidget* parent) :
   m_width(x),
   m_height(y),
   m_parent(parent),
   m_percent(50)
{
   m_space = new CGUISpace(m_width,m_height);
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
   //Draw percents
   painter->setPen(Qt::white);
   QString percentStr("Perc:");
   percentStr.append(QVariant(quint16(m_percent)).toString());
   percentStr.append("%");
   painter->drawText(m_width - 80, 30, percentStr);
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
            && (y >= std::min(beginY, endY)) && (y <= std::max(beginY,endY))
            && (pl->GetPlayerId() == m_playerId))
      {
         currPl->MakeActive();
      }
      else
      {
         currPl->ReleaseActive();
      }
   }
}

void CGUIView::Target(unsigned int clickX, unsigned int clickY)
{
   std::vector<unsigned int> departure;
   unsigned int destination;
   unsigned int playerId;
   CGUIPlanet* currPl;
   foreach(currPl, m_planets)
   {
      if (currPl->IsActive())
      {
         departure.push_back(currPl->GetPlanet()->GetId());
      }
      unsigned int x(0), y(0);
      currPl->GetPlanet()->GetPosition(x,y);
      if ((abs(clickX - x) < currPl->GetPlanet()->GetRadius()) &&
            (abs(clickY - y) < currPl->GetPlanet()->GetRadius()))
      {
            destination = currPl->GetPlanet()->GetId();
      }
   }
   playerId = m_playerId;

}

unsigned int CGUIView::GetPercent() const
{
   return m_percent;
}

unsigned int CGUIView::GetPlayerId() const
{
   return m_playerId;
}

void CGUIView::SetPercent(unsigned int percent)
{
   m_percent = percent;
}

void CGUIView::SetPlayerId(unsigned int id)
{
   m_playerId = id;
}
