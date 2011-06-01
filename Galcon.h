#ifndef GALCON_H
#define GALCON_H

#include <QObject>

#include "GUI/gui.h"
#include "serverManager/ServerManager.h"
#include "Game.h"

class CGalcon : public QObject
{

   Q_OBJECT

public:
   CGalcon();

private:

   CGUI* m_gui;
   CGame* m_game;
   ::ServerManagerDecl::CServerManager* m_manager;

public:
   void connectSendersToTakers();
};

#endif // GALCON_H
