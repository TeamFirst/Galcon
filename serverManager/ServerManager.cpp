#include <QString>

#include "ServerManager.h"

namespace ServerManagerDecl
{
/// constructor
   CServerManager::CServerManager():
      m_connectToServer(false)
   {
   }

   CServerManager::~CServerManager()
   {
   }

/// private function
   void CServerManager::connectToServer(const std::string& serverIP,
      const unsigned int m_serverPort)
   {
      m_tcpSocket = new QTcpSocket(this);

      m_tcpSocket->connectToHost(QString(serverIP.c_str()), m_serverPort);
      connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
      connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
      connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
         this,SLOT(slotError(QAbstractSocket::SocketError)));
   }

   void CServerManager::sendToServer(const Message::IMessagePtr pMessage)
   {
      QByteArray  arrBlock;
      QDataStream out(&arrBlock, QIODevice::WriteOnly);
      out.setVersion(QDataStream::Qt_4_7);
      out << quint16(0) << QString(pMessage->toString().c_str()).toUtf8();

      out.device()->seek(0);
      out << quint16(arrBlock.size() - sizeof(quint16));

      m_tcpSocket->write(arrBlock);
   }

   void CServerManager::parseStrFromServer(const std::string& sMes)
   {
      switch(m_parser.CheckTypeMessage(sMes))
      {
      case CParser::eConfirmConnect :
         SendConfirmConnect(m_parser.ParseMConfirmConnect(sMes));
         break;
      case CParser::eError :
         SendError(m_parser.ParseMError(sMes));
         break;
      case CParser::eFinishGame :
         SendFinishGame(m_parser.ParseMFinishGame(sMes));
         break;
      case CParser::eStartGame :
         SendStartGame(m_parser.ParseMStartMapGame(sMes));
         break;
      case CParser::eStateMap :
         SendStateMap(m_parser.ParseMStateMap(sMes));
         break;
      case CParser::eTimeToStart :
         SendTimeToStart(m_parser.ParseMTimeToStartGame(sMes));
         break;
      case CParser::eUnknown :
         break;
      }
   }

/// slots connect to server
   void CServerManager::slotConnected()
   {
      m_connectToServer = true;

      SendInError("Connected");
   }

   void CServerManager::slotReadyRead()
   {
      QDataStream in(m_tcpSocket);
      in.setVersion(QDataStream::Qt_4_7);
      qint16 nextBlockSize = 0;
      for (;;)
      {
          if (m_tcpSocket->bytesAvailable() < sizeof(quint8))
          {
              break;
          }

          in >> nextBlockSize;

          if (m_tcpSocket->bytesAvailable() < nextBlockSize)
          {
              break;
          }

          QByteArray str;
          in >> str;

          nextBlockSize = 0;

          SendInError(QString(str).toStdString());

          parseStrFromServer(QString(str).toStdString());
      }
   }

   void CServerManager::slotError(QAbstractSocket::SocketError)
   {
      m_connectToServer = false;

      SendInError("Error connection");
   }

/// public slots
   void CServerManager::TakeServerConnect(const Message::CMessageConnectToServerPtr pMessage)
   {
      if(!m_connectToServer)
      {
         connectToServer(pMessage->m_serverIP, pMessage->m_serverPort);
         sendToServer(pMessage);
      }
      else
      {         
        SendInError("Error, You again trying connect to server");
      }
   }

   void CServerManager::TakeStepPlayer(const Message::CMessageStepPlayerPtr pMessage)
   {
      if(m_connectToServer)
      {
         sendToServer(pMessage);
      }
      else
      {         
         SendInError("Error, No connection to server");
      }
   }

} // namespace ServerManagerDecl
