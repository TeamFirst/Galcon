#include "GUIView.h"
#include <vector>
using namespace std;
CGUIView::CGUIView(QObject *parent) :
    QObject(parent)
{
}

CGUIView::~CGUIView()
{

}

void CGUIView::OnShowView()
{


}
void CGUIView::OnHideView()
{


}

void CGUIView::OnUpdate(const std::vector<CPlanet* >& planets, const std::list<CFleet* >& fleets)
{
    m_planets = planets;
    m_fleets = fleets;
    emit sUpdate();

}
const std::vector<CPlanet *> * CGUIView::GetPlanets() const
{


}
const std::vector<CPlanet *> * CGUIView::GetFleets() const
{


}

