#ifndef CGAME_H
#define CGAME_H
#include <QObject>

#include "SceneUpdates.h"
#include "Space.h"
#include "message/MessageAddView.h"
#include "message/MessageFinishGame.h"

typedef int IMessage;

class CGame : public QObject
{
   Q_OBJECT

public:
   CGame();

signals:
   void SendStartGame();
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
   unsigned long m_timeTick;
};

#endif // CGAME_H
