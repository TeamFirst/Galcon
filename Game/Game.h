#pragma once

#include <QObject>
#include <QTimer>

#include "SceneUpdates.h"
#include "Space.h"
#include "message/MessageAddView.h"
#include "message/MessageFinishGame.h"

namespace Game
{

   class CGame : public QObject
   {
      Q_OBJECT

   public:
      CGame();
      static const unsigned long m_timeTick = 1000;

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

      ISceneUpdates* m_view;
      CSpace* m_space;
      QTimer* m_timer;
   };
} // Namespace Game

