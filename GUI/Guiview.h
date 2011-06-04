#ifndef GUIVIEW_H
#define GUIVIEW_H

#include <QWidget>
#include "Guiplanet.h"
#include "Guifleet.h"
#include "SceneUpdates.h"
#include "Guispace.h"

class CGUIView : public ISceneUpdates
{
public:
    explicit CGUIView(unsigned int x, unsigned int y, QWidget* parent);
    ~CGUIView();
    void OnShowView();
    void OnHideView();
    void OnUpdate(const std::vector<CPlanet *> &, const std::list<CFleet *> &);

    void Draw(QPainter* painter);

    void Selection(unsigned int beginX, unsigned int beginY,
                   unsigned int endX, unsigned int endY);
private:
   unsigned int m_width;
   unsigned int m_height;
   unsigned int m_percent;

   std::vector<CGUIPlanet*> m_planets;
   std::list<CGUIFleet*> m_fleets;
   CGUISpace* m_space;

   QWidget* m_parent;
};

#endif // GUIVIEW_H
