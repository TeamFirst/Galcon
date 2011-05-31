#include "messageconnecttoserver.h"

CMessageConnectToServer::CMessageConnectToServer(const QString & i_namePlayer, const QString & i_serverIP, int i_serverPort)
    :IMessage::m_type(IMessage::eMessageConnectToServer),
    m_namePlayer(i_namePlayer),
    m_serverIP(i_serverIP),
    m_serverPort(i_serverPort)
{
}
int CMessageConnectToServer::GetTypeMessage() const
{
    return m_type;
}
