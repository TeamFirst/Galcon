#ifndef GUIVIEW_H
#define GUIVIEW_H

#include <QWidget>
#include "Guiplanet.h"
#include "Guifleet.h"
#include "SceneUpdates.h"

class CGUIView : public ISceneUpdates
{
public:
    explicit CGUIView(unsigned int x, unsigned int y, QWidget* parent);
    ~CGUIView();
    void OnShowView();
    void OnHideView();
    void OnUpdate(const std::vector<CPlanet *> &, const std::list<CFleet *> &);

    void Draw(QPainter* painter);
private:
   unsigned int m_width;
   unsigned int m_height;

   std::vector<CGUIPlanet> m_planets;
   std::list<CGUIFleet> m_fleets;

   QWidget* m_parent;
};

#endif // GUIVIEW_H
