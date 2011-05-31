#ifndef SCENEUPDATE_H
#define SCENEUPDATE_H

class ISceneUpdate
{
   ISceneUpdate();
   virtual ~ISceneUpdate() = 0;

   virtual OnShowView();
   virtual OnHideView();

   virtual OnUpdate(const std::vector<CPlanet* >&, const std::list<CFleet* >&);
};

#endif // SCENEUPDATE_H
