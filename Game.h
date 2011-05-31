#ifndef CGAME_H
#define CGAME_H
#include <QObject>
#include "SceneUpdate.h"
#include "Space.h"

typedef int IMessage;

class CGame : public QObject
{
   Q_OBJECT

public:
   CGame();
   void AddView(IMessage* );
   void SendStartGame(IMessage*);
   void DeleteGame(IMessage*);
   void signalTimer();
   void slotTimer();
   void SlotStartData(IMessage*);
   void SlotStateMap(IMessage*);
   void SlotFinishGame(IMessage*);
private:
   ISceneUpdate* m_view;
   CSpace* m_space;
};

#endif // CGAME_H
