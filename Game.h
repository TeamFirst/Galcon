#ifndef CGAME_H
#define CGAME_H
#include <QObject>

typedef int IMessage;

class CGame : public QObject
{
   Q_OBJECT

public:
   CGame();
   ~CGame();
   void SlotStartData(IMessage*);
   void SlotStateMap(IMessage*);
   void SlotFinishGame(IMessage*);

};

#endif // CGAME_H
