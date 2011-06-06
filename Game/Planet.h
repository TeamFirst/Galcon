#pragma once

/// @file Planet.h
/// @brief CPlanet declaration header
/// @author Dmitriy Kozhevnikov
/// @date 06-June-2011

namespace Game
{
   /// @class CPlanet
   /// @brief Planet management class

   class CPlanet
   {
   public:
      CPlanet(const unsigned short id, const unsigned short x, const unsigned short y,
              const unsigned short radius, const unsigned long army,
              const unsigned short playerId);

      unsigned long GetArmy() const;
      unsigned short GetPlayerId() const;
      void GetPosition(unsigned int& x, unsigned int& y) const;
      unsigned int GetRadius() const;
      unsigned short GetId() const;

      void SetArmy (const unsigned long army);
      void SetPlayer (const unsigned short playerId);

   private:
      unsigned short m_id;
      unsigned short m_x;
      unsigned short m_y;
      unsigned short m_radius;
      double m_army;
      unsigned short m_playerId;
   };
} // Namespace Game

