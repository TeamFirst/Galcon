#pragma once

#include <string>

class CPlayer
{
public:
   CPlayer(unsigned short i_id, std::string i_name): m_id(i_id), m_name(i_name){}
   ~CPlayer();

   unsigned short GetId() const;

   std::string GetName() const;

private:
   unsigned short m_id;
   std::string m_name;
};
