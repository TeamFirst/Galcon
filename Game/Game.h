#pragma once

#include <QObject>
#include <QTimer>

#include "GUI/SceneUpdates.h"
#include "Space.h"
#include "../Player.h"
#include "message/MessageAddView.h"
#include "message/MessageFinishGame.h"

namespace Game
{
   class CGame : public QObject
   {
      Q_OBJECT

   public:
      CGame(std::vector<CPlayer* >* players);
      static const unsigned long m_timeTick = 100;

   signals:
      void SendStartGame(unsigned int mapX, unsigned int mapY);
      void signalTimer();

   public slots:
      void SlotStartData(Message::CMessageStartMapGamePtr data);
      void SlotStateMap(Message::CMessageStateMapPtr data);
      void SlotFinishGame(Message::CMessageFinishGamePtr mes);

      void AddView(Message::CMessageAddViewPtr mes);
      void DeleteGame();
      void slotTimer();

   private:
      std::vector<CPlayer* >* m_players;
      GUI::ISceneUpdates* m_view;
      CSpace* m_space;
      QTimer* m_timer;
   };
} // Namespace Game

