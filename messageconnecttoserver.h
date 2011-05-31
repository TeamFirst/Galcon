#ifndef MESSAGECONNECTTOSERVER_H
#define MESSAGECONNECTTOSERVER_H
#include "Message.h"
struct CMessageConnectToServer : public IMessage
{
public:
    CMessageConnectToServer(const QString & i_namePlayer, const QString & i_serverIP, int i_serverPort);
    const QString m_namePlayer;
    const QString m_serverIP;
    const int m_serverPort;
};

#endif // MESSAGECONNECTTOSERVER_H
