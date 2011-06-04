#include "MapGame.h"

namespace SingleGame
{

   CMapGame::CMapGame()
   {
   }

   CMapGame::~CMapGame()
   {
   }

/// generation start data
   void CMapGame::GenerationMap(
      const unsigned int widthMap,
      const unsigned int heigthMap,
      const unsigned int flySpeed,
      const unsigned int growSpeed)
   {
      m_widthMap = widthMap;
      m_heigthMap = heigthMap;
      m_flySpeed = flySpeed;
      m_growSpeed = growSpeed;
   }

   void CMapGame::SetPlayers(const std::vector<CPlayer>& vPlayer)
   {
   }

} // namespace SingleGame

