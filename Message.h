#ifndef IMESSAGE_H
#define IMESSAGE_H

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

   ETypeMessage m_type;
   int GetTypeMessage();
};

#endif // IMESSAGE_H
