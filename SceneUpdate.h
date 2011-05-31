#ifndef SCENEUPDATE_H
#define SCENEUPDATE_H

#include <vector>

#include "Planet.h"
#include "Fleet.h"

class ISceneUpdate
{
   ISceneUpdate();
   virtual ~ISceneUpdate() = 0;

   virtual void OnShowView();
   virtual void OnHideView();

   virtual void OnUpdate(const std::vector<CPlanet* >&, const std::list<CFleet* >&);
};

#endif // SCENEUPDATE_H
