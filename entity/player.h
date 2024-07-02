#pragma once

#include "entity.cpp"
#include "../item/meleeweapon/sword.cpp"
// #include "../GUI/playergui.cpp"

class entity;

class player : public entity {

private:
  bool m_attacking;
  sword m_sword;

 inline void initvar();
 inline void initanimation();
public:
  player(const float& x, const float& y ,sf::Texture& texture);
  virtual ~player();

  inline attributecomponet* getattributecomponet()const;
  inline const float hppercent()const;
  inline std::string gethpandhpmax()const;
  inline const float exppercent()const;
  inline std::string getexpandexpnext()const;
  inline const int& getlevel()const;
  
  inline void losehp(const int& hp);
  inline void gainhp(const int& hp);
  inline void loseexp(const int& exp);
  inline void gainexp(const int& exp);

  void updateattack();
  void updateanimation(const float& dt);
  void update(const float& dt,const sf::Vector2f& mouse_pos_view);
  void render(sf::RenderTarget& target, sf::Shader* shader = nullptr,const bool& show_hitbox = false);
};