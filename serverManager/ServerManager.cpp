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
   void CServerManager::connectToServer(const std::string serverIP, const unsigned int m_serverPort)
   {
      m_tcpSocket = new QTcpSocket(this);

      m_tcpSocket->connectToHost(QString(serverIP.c_str()), m_serverPort);
      connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
      connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
      connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));

   }

   void CServerManager::sendToServer(const Message::IMessagePtr pMessage)
   {
      QByteArray  arrBlock;
      QDataStream out(&arrBlock, QIODevice::WriteOnly);
      out.setVersion(QDataStream::Qt_4_7);
      out << quint16(0) << QString(pMessage->toString().c_str());

      out.device()->seek(0);
      out << quint16(arrBlock.size() - sizeof(quint16));

      m_tcpSocket->write(arrBlock);
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

          QString str;
          in >> str;

          QMessageBox msgBox;
          msgBox.setText(str);
          msgBox.exec();

          nextBlockSize = 0;
      }
   }

   void CServerManager::slotError(QAbstractSocket::SocketError)
   {

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
         std::string str = pMessage->toString();
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
