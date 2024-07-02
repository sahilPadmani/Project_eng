#pragma once

#include "../source/animationcomponent.cpp"
#include "../source/hitbox.cpp"
#include "../source/movment.cpp"
#include "../source/attributecomponet.cpp"
#include "../source/skillcomponet.cpp"

class hitbox;
class movment;
class animationcomponent;
class attributecomponet;
class skillcomponet;


class entity {
private:
protected:
  sf::Sprite m_sprite;

  hitbox *m_hitbox;
  movment *m_movment;
  animationcomponent *m_animation;
  attributecomponet* m_attribute;
  skillcomponet* m_skill;

public:
  entity();
  virtual ~entity();

  // component
  inline void setspritetexture(const sf::Texture &texture);
  inline void createhitbox(const float &x, const float &y, const float &height,
                    const float &width);
  inline void createmovment(const float &maxvalocity, const float &acceleration,
                     const float &deceleration);
  inline void createanimation(sf::Texture &texture);
  inline void createattribute(const unsigned& level);
  inline void createatskill();

  virtual inline const sf::Vector2f &getentitypos() const;
  virtual inline const sf::Vector2f getentitycenter()const;
  virtual inline const sf::FloatRect getglobalbound() const;
  virtual inline const sf::Vector2i getgridpos(const int& gridsize)const;
  virtual inline const sf::FloatRect getnextbound(const float& dt)const;

  virtual void setposition(const float &x, const float &y);
  virtual void move(const float &dt, const float &dir_x, const float &dir_y);
  virtual void stopvelocity();
  virtual void stopvelocityX();
  virtual void stopvelocityY();

  virtual void update(const float &dt,const sf::Vector2f& mouse_pos_view) = 0;
  virtual void render(sf::RenderTarget &target,sf::Shader* shader = nullptr,const bool& show_hitbox = false) = 0;
};