#pragma once

#include "../header/animationcomponent.h"

animationcomponent::animationcomponent(sf::Sprite &sprite, sf::Texture &texture)
    : m_sprite(sprite), m_texture(texture), m_lastanimation(NULL) {
  m_priorityanimation = NULL;
}

animationcomponent::~animationcomponent() {
  for (std::pair<const std::string, animation *> &i : m_animation) {
    delete i.second;
  }
}

inline void animationcomponent::addanimation(
    const std::string &key, const float &animationtimer,
    const int &startframe_x, const int &startframe_y, const int &endframes_x,
    const int &endframes_y, const int &hight, const int &width) {
  m_animation[key] =
      new animation(m_sprite, m_texture, animationtimer, startframe_x,
                    startframe_y, endframes_x, endframes_y, hight, width);
}

inline const bool &animationcomponent::isDone(const std::string &key) {
  return m_animation[key]->isdone();
}

inline const bool &animationcomponent::startanimation(const std::string &key,
                                               const float &dt,
                                               const float &mode) {
  if (m_lastanimation != m_animation[key]) {

    if (m_lastanimation != NULL)
      m_animation[key]->reset();
    m_lastanimation = m_animation[key];
  }

  return m_animation[key]->play(dt, std::abs(mode));
}

// void animationcomponent::pauseanimation(const std::string& animation){}

// void animationcomponent::resetanimation(const std::string& animation){}

const bool &animationcomponent::play(const std::string &key, const float &dt,
                                     const float &modifier,
                                     const float &modifier_max,
                                     const bool priority) {
  if (m_priorityanimation) {
    if (m_priorityanimation == m_animation[key]) {
      if (startanimation(key, dt,
                         static_cast<float>(modifier / modifier_max))) {
        m_priorityanimation = NULL;
      }
    }
  } else {
    if (priority)
      m_priorityanimation = m_animation[key];
    startanimation(key, dt, static_cast<float>(modifier / modifier_max));
  }
  return m_animation[key]->isdone();
}