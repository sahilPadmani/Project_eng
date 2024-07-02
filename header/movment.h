#pragma once

#include "../preheader.hpp"

enum movment_state{STAND = 0 ,MOVELEFT ,MOVERIGHT ,MOVEUP ,MOVEDOWN };
class movment {
    
  sf::Sprite& m_sprite;

  float m_maxvalocity;
  float m_acceleration;
  float m_deceleration;

  sf::Vector2f m_valocity;

public:
  movment(sf::Sprite& sprite , const float& valocity , const float&  acceleration ,const float& deceleration);
  virtual ~movment();

  inline void stopvelocity();
  inline void stopvelocityX();
  inline void stopvelocityY();

  inline const float& getmaxvalocity() const;
  inline const sf::Vector2f &getvalocity() const;
  inline const bool getmovstate(const short& state) const;

  inline void move(const float& dt,const float &dir_x, const float &dir_y);
  void update(const float &dt);
};