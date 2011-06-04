#include "SingleGameManager.h"

namespace SingleGame
{
/// constructor
   CSingleGameManager::CSingleGameManager()
   {
   }

   CSingleGameManager::~CSingleGameManager()
   {
   }

/// publoc slots
   void CSingleGameManager::TakeServerConnect(const Message::CMessageConnectToServerPtr pMessage)
   {
   }

   void CSingleGameManager::TakeStepPlayer(const Message::CMessageStepPlayerPtr pMessage)
   {
   }

/// generation start data
   void CSingleGameManager::startGame(
      const unsigned int timeToStart,
      const unsigned int widthMap,
      const unsigned int heigthMap,
      const unsigned int flySpeed,
      const unsigned int growSpeed,
      const std::string& namePlayer
      )
   {
      //m_vPlayer.push_back();
   }


} // namespace SingleGame
