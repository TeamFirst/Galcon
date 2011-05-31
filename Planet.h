#ifndef CPLANET_H
#define CPLANET_H

class CPlanet
{
public:
   CPlanet(unsigned short id, unsigned short x, unsigned short y,
           unsigned short radius, unsigned long army, unsigned short playerId);

   unsigned long GetArmy() const;
   unsigned int GetPlayerId() const;
   void GetPosition(unsigned int& x, unsigned int& y) const;
   unsigned int GetRadius() const;
   unsigned short GetId() const;

   void SetArmy (const unsigned long army);
   void SetPlayer (const unsigned int playerId);

private:
   unsigned short m_id;
   unsigned short m_x;
   unsigned short m_y;
   unsigned short m_radius;
   double m_army;
   unsigned short m_playerId;
};

#endif // CPLANET_H
