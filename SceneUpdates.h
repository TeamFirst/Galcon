#ifndef SCENEUPDATES_H
#define SCENEUPDATES_H

#include <vector>

#include "Planet.h"
#include "Fleet.h"

class ISceneUpdates
{

public:

   ISceneUpdates();
   virtual ~ISceneUpdates() = 0;

   virtual void OnShowView();
   virtual void OnHideView();

   virtual void OnUpdate(const std::vector<CPlanet* >&, const std::list<CFleet* >&);
};

#endif // SCENEUPDATE_H
