
#ifndef GALCON_H
#define GALCON_H

#include <QObject>

#include "GUI/Gui.h"
#include "serverManager/ServerManager.h"
#include "Game/Game.h"
#include "SingleGame/SingleGameManager.h"

class CGalcon : public QObject
{

   Q_OBJECT

public:
   CGalcon();

private:
   void connectSendersToTakers();

   GUI::CGUI* m_gui;
   Game::CGame* m_game;
   ServerManagerDecl::CServerManager* m_manager;
   SingleGame::CSingleGameManager* m_singleGame;
};

#endif // GALCON_H

