#pragma once
#include "../item.cpp"

class item;

class meleeweapon : public item {
private:
protected:
  int p_damagemin;
  int p_damagemax;

  sf::Sprite p_sprite;
  sf::Texture p_texture;

public:
  meleeweapon();
  virtual ~meleeweapon();

  virtual void update(const sf::Vector2f& mouseview,const sf::Vector2f& center) = 0;
  virtual void render(sf::RenderTarget& target,const sf::Shader* shader = nullptr) = 0;
};