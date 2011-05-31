#ifndef IMESSAGE_H
#define IMESSAGE_H
#include <QSharedPointer>

struct IMessage;
typedef QSharedPointer<IMessage> pIMessage;

struct IMessage
{
   enum ETypeMessage{
      eMessageConnectToServer,
      eMessageConfirmationConnectToServer,
      eMessageTimeToStartGame,
      eMessageStartMapGame,
      eMessageStepPlayer,
      eMessageStateMap,
      eMessageFinishGame,
      eMessageError,
      eMessageAddView,
   };
   virtual int GetTypeMessage() const = 0;
protected:
   ETypeMessage m_type;
};

#endif // IMESSAGE_H
