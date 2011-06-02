#include <QMessageBox>
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
      out << quint8(0) << QString(pMessage->toString().c_str()).toUtf8();

      out.device()->seek(0);
      out << quint8(arrBlock.size() - sizeof(quint8));

      m_tcpSocket->write(arrBlock);
   }

   void CServerManager::parseStrFromServer(const std::string& sMes)
   {
      switch(m_parser.CheckTypeMessage(sMes))
      {
      case CParser::eConfirmConnect :
         this->SendConfirmConnect(
         m_parser.ParseMConfirmConnect(sMes));
         break;
      case CParser::eError :
         m_parser.ParseMError(sMes);
         break;
      case CParser::eFinishGame :
         m_parser.ParseMFinishGame(sMes);
         break;
      case CParser::eStartGame :
         m_parser.ParseMStartMapGame(sMes);
         break;
      case CParser::eStateMap :
         m_parser.ParseMStateMap(sMes);
         break;
      case CParser::eTimeToStart :
         this->SendTimeToStart(
         m_parser.ParseMTimeToStartGame(sMes));
         break;
      case CParser::eUnknown :
         break;
      }
   }

/// slots connect to server
   void CServerManager::slotConnected()
   {
      m_connectToServer = true;

      QMessageBox msgBox;
      msgBox.setText("Connected");
      msgBox.exec();
   }

   void CServerManager::slotReadyRead()
   {
      QDataStream in(m_tcpSocket);
      in.setVersion(QDataStream::Qt_4_7);
      qint8 nextBlockSize = 0;
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

          QMessageBox msgBox;
          msgBox.setText(QString(str));
          msgBox.exec();

          nextBlockSize = 0;

          parseStrFromServer(QString(str).toStdString());
      }
   }

   void CServerManager::slotError(QAbstractSocket::SocketError)
   {
      m_connectToServer = false;

      QMessageBox msgBox;
      msgBox.setText("Error connection");
      msgBox.exec();
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
         QMessageBox msgBox;
         msgBox.setText("Error, You again trying connect to server");
         msgBox.exec();
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
         QMessageBox msgBox;
         msgBox.setText("Error, No connection to server");
         msgBox.exec();
      }
   }

} // namespace ServerManagerDecl
