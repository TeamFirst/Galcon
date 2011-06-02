<<<<<<< HEAD
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
   void connectSendersToTakers();

   CGUI* m_gui;
   CGame* m_game;
   ::ServerManagerDecl::CServerManager* m_manager;
};

#endif // GALCON_H
=======
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
>>>>>>> 04797c5b5eb9328ccd27e5ad3dcc8191ee169040
