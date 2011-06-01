#ifndef GUIVIEW_H
#define GUIVIEW_H

#include <QObject>
#include "../SceneUpdates.h"

class CGUIView : public QObject, public ISceneUpdates
{
    Q_OBJECT
public:
    explicit CGUIView(QObject *parent = 0);
    virtual ~CGUIView();

    virtual void OnShowView();
    virtual void OnHideView();

    const std::vector<CPlanet *> * GetPlanets() const;
    const std::list<CFleet* > * GetFleets() const;

    virtual void OnUpdate(const std::vector<CPlanet* >&, const std::list<CFleet* >&);

signals:
    void sUpdate();

public slots:

private:
    std::vector<CPlanet *> m_planets;
    std::list<CFleet* > m_fleets;


};

#endif // GUIVIEW_H
