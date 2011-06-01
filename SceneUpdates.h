#ifndef SCENEUPDATES_H
#define SCENEUPDATES_H

#include <vector>
#include <list>
#include "Planet.h"
#include "Fleet.h"

class ISceneUpdates
{

public:
// Do we realy need it?
//   ISceneUpdates()
//   {}
   virtual ~ISceneUpdates()
   {}

   virtual void OnShowView() = 0;
   virtual void OnHideView() = 0;

   virtual void OnUpdate(const std::vector<CPlanet* >&, const std::list<CFleet* >&) = 0;
};

#endif // SCENEUPDATE_H
