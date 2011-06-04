#include <QString>

#include "ServerManager.h"

namespace ServerManagerDecl
{
/// constructor
   CServerManager::CServerManager():
      m_connectToServer(false),
      m_parser()
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
         emit SendConfirmConnect(m_parser.ParseMConfirmConnect(sMes));
         break;
      case CParser::eError :
         emit SendError(m_parser.ParseMError(sMes));
         break;
      case CParser::eFinishGame :
         emit SendFinishGame(m_parser.ParseMFinishGame(sMes));
         break;
      case CParser::eStartGame :
         emit SendStartGame(m_parser.ParseMStartMapGame(sMes));
         break;
      case CParser::eStateMap :
         emit SendStateMap(m_parser.ParseMStateMap(sMes));
         break;
      case CParser::eTimeToStart :
         emit SendTimeToStart(m_parser.ParseMTimeToStartGame(sMes));
         break;
      case CParser::eUnknown :
         Message::CMessageInformationPtr ptr(new Message::CMessageInformation);
         ptr->m_typeInformation = Message::CMessageInformation::eMessageFromServer;
         ptr->m_strInformation = "Error, Server send unknown message";
         emit SendInInformation(ptr);
         break;
      }
   }

/// slots connect to server
   void CServerManager::slotConnected()
   {
      m_connectToServer = true;

      Message::CMessageInformationPtr ptr(new Message::CMessageInformation);
      ptr->m_typeInformation = Message::CMessageInformation::eConnectionToServer;
      ptr->m_strInformation = "Connected";
      emit SendInInformation(ptr);
   }

   void CServerManager::slotReadyRead()
   {
      QDataStream in(m_tcpSocket);
      in.setVersion(QDataStream::Qt_4_7);
      qint16 nextBlockSize = 0;
      for (;;)
      {
          if (m_tcpSocket->bytesAvailable() < sizeof(quint16))
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

          Message::CMessageInformationPtr ptr(new Message::CMessageInformation);
          ptr->m_typeInformation = Message::CMessageInformation::eMessageFromServer;
          ptr->m_strInformation = QString(str).toStdString();
          emit SendInInformation(ptr);

          parseStrFromServer(QString(str).toStdString());
      }
   }

   void CServerManager::slotError(QAbstractSocket::SocketError)
   {
      m_connectToServer = false;

      Message::CMessageInformationPtr ptr(new Message::CMessageInformation);
      ptr->m_typeInformation = Message::CMessageInformation::eConnectionToServer;
      ptr->m_strInformation = "Error connection";
      emit SendInInformation(ptr);
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
         Message::CMessageInformationPtr ptr(new Message::CMessageInformation);
         ptr->m_typeInformation = Message::CMessageInformation::eConnectionToServer;
         ptr->m_strInformation = "Error, You again trying connect to server";
         emit SendInInformation(ptr);
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
         Message::CMessageInformationPtr ptr(new Message::CMessageInformation);
         ptr->m_typeInformation = Message::CMessageInformation::eConnectionToServer;
         ptr->m_strInformation = "Error, No connection to server";
         emit SendInInformation(ptr);
      }
   }

} // namespace ServerManagerDecl
