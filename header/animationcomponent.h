#pragma once

#include "../preheader.hpp"

class animationcomponent {
private:
  class animation {
  public:
    sf::Sprite &m_spriteanimation;
    sf::Texture &m_texturesheet;
    float m_animationtimer;
    float m_timer;
    bool m_done;
    int m_hight;
    int m_width;
    sf::IntRect m_startrect;
    sf::IntRect m_currentrect;
    sf::IntRect m_endrect;

    animation(sf::Sprite &sprite, sf::Texture &texturesheet,
              const float &animationtimer, const int &startframe_x,
              const int &startframe_y, const int &endframes_x, const int &endframes_y,
              const int &hight, const int &width)
        : m_spriteanimation(sprite), m_texturesheet(texturesheet) {
      m_timer = 0.f;
      m_done = false;
      m_animationtimer = animationtimer;
      m_hight = hight;
      m_width = width;
      m_startrect = sf::IntRect(startframe_x * m_width, startframe_y * m_hight, m_width, m_hight);
      m_currentrect = m_startrect;
      m_endrect = sf::IntRect(endframes_x * m_width, endframes_y * m_hight, m_width, m_hight);

      m_spriteanimation.setTexture(m_texturesheet, true);
      m_spriteanimation.setTextureRect(m_currentrect);
    }

    //accesser
    inline const bool& isdone()const{
      return this->m_done;
    }

    const bool& play(const float &dt,float mode ) {
      
      m_done = false;
      if(mode < 0.5f)
        mode = 0.5f;
      m_timer += mode * 100.f * dt;

      if (m_timer >= m_animationtimer) {
        m_timer = 0.f;
        if (m_currentrect != m_endrect) {
          m_currentrect.left += m_width;
        } else {
          m_currentrect.left = m_startrect.left;
          m_done = true;
        }
        m_spriteanimation.setTextureRect(m_currentrect);
      }
      return m_done;
    }

    inline void reset(){
      m_timer = 0.f;
      m_currentrect = m_startrect;
    }
  };

  sf::Sprite &m_sprite;
  sf::Texture &m_texture;
  std::map<std::string, animation*> m_animation;
  animation* m_lastanimation;
  animation* m_priorityanimation;

public:
  animationcomponent(sf::Sprite &sprite, sf::Texture &texture);
  virtual ~animationcomponent();

  inline const bool& isDone(const std::string& key);

  inline void addanimation(const std::string& key,
              const float &animationtimer, const int &startframe_x,
              const int &startframe_y, const int &endframes_x, const int &endframes_y,
              const int &hight, const int &width);


  // void pauseanimation(const std::string& animation);
  // void resetanimation(const std::string& animation);

  inline const bool& startanimation(const std::string& key,const float& dt,const float& mode);
  const bool& play(const std::string& key,const float& dt,const float& modifier , const float& modifier_max , const bool priority = false);
};