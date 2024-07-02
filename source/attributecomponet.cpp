#pragma once
#include "../header/attributecomponet.h"

attributecomponet::attributecomponet(const int &level) {
  this->level = level;
  this->exp = 0;
  this->expnext = static_cast<int>((50/3)*(pow(this->level + 1,3) - 6 * pow(this->level + 1,2) + ((this->level + 1) * 17 ) - 12));
  this->attributepoints = 2;

  this->vitality  = 1;
  this->strength  = 1;
  this->dexterity = 1;
  this->agility = 1;
  this->intelligence =1;

  updatelevel();
  updatestats(true);
}

attributecomponet::~attributecomponet() {
  // TODO: Needs implementation
}

inline void attributecomponet::losehp(const int &hp) {
  this->hp -= hp;
  if (this->hp < 0)
    this->hp = 0;
}
inline void attributecomponet::gainhp(const int &hp) {
  this->hp += hp;
  if (this->hp > this->hpmax)
    this->hp = this->hpmax;
}
inline void attributecomponet::loseexp(const int &exp) {
  this->exp -= exp;
  if (this->exp < 0)
    this->exp = 0;
}
inline void attributecomponet::gainexp(const int& exp){
    this->exp += exp;
    updatelevel();
}

inline void attributecomponet::updatestats(const bool& resethp) {

    int extra = this->intelligence/5;

    this->hpmax = this->vitality * 7 + this->vitality + this->strength/2 + extra;
    this->damagemin = this->strength * 2 + this->strength / 4 + extra;
    this->damagemax = this->strength * 2 + this->strength / 2 + extra;
    this->accuracy = this->dexterity * 5 + this->dexterity /2 + extra;
    this->defence = this->agility * 2 + this->agility /4 + extra;
    this->luck = this->intelligence * 2 + extra;

    if(resethp)
        this->hp = this->hpmax;
}

void attributecomponet::updatelevel(){
    while (this->exp >= this->expnext) {
        ++level;
        exp -= expnext;
        expnext = static_cast<int>((50/3)*(pow(this->level + 1,3) - 6 * pow(this->level+1,2) + ((this->level+1) * 17 ) - 12));
        ++attributepoints;
    }
}

inline void attributecomponet::update(){
    updatelevel();
}