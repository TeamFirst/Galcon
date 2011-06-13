#include "Player.h"

unsigned short CPlayer::GetId() const
{
   return m_id;
}

std::string CPlayer::GetName() const
{
   return m_name;
}

unsigned long CPlayer::GetArmy() const
{
   return m_army;
}

void CPlayer::SetArmy(const unsigned long army)
{
   m_army += army;
}

void CPlayer::NullArmy()
{
   m_army = 0;
}
