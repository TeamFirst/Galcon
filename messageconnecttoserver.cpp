#include "messageconnecttoserver.h"

CMessageConnectToServer::CMessageConnectToServer()
    :IMessage::m_type(IMessage::eMessageConnectToServer)
{
}
int CMessageConnectToServer::GetTypeMessage() const
{
    return m_type;
}
