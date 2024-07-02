#pragma once

#include "../preheader.hpp"
struct attributecomponet {
  // Leveling
  int level;
  int exp;
  int expnext;
  int attributepoints;

  // attributes
  int vitality;
  int strength;
  int dexterity;
  int agility;
  int intelligence;

  // stats
  int hp;
  int hpmax;
  int damagemin;
  int damagemax;
  int accuracy;
  int defence;
  int luck;

  attributecomponet(const int &level);
  virtual ~attributecomponet();

  inline void losehp(const int &hp);
  inline void gainhp(const int &hp);
  inline void loseexp(const int &exp);
  inline void gainexp(const int &exp);

  inline void updatestats(const bool &resethp);
  void updatelevel();
  inline void update();
};
