
#ifndef GALCON_H
#define GALCON_H

#include <QObject>

#include "GUI/gui.h"
#include "serverManager/ServerManager.h"
#include "Game/Game.h"

class CGalcon : public QObject
{

   Q_OBJECT

public:
   CGalcon();

private:
   void connectSendersToTakers();

   CGUI* m_gui;
   CGame* m_game;
   ::ServerManagerDecl::CServerManager* m_manager;
};

#endif // GALCON_H

