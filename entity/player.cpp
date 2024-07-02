#pragma once

#include "player.h"

inline void player::initvar() { m_attacking = false; }

inline void player::initanimation (){
  m_animation->addanimation("IDEL", 15.f, 0, 0, 8, 0, 64, 64);
  m_animation->addanimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
  m_animation->addanimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
  m_animation->addanimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
  m_animation->addanimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
  // m_animation->addanimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}
player::player(const float &x, const float &y, sf::Texture &texture) {
  
  initvar();
  createhitbox(12.f, 0.f, 64.f, 40.f);
  createmovment(200.f, 1600.f, 1000.f);
  createanimation(texture);
  createattribute(1);
  createatskill();

  setposition(x, y);
  initanimation();
}

player::~player() {}
inline void player::updateattack() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
    m_attacking = true;
  }
}

inline attributecomponet *player::getattributecomponet() const { return m_attribute; }

inline const float player::hppercent() const {
  return static_cast<float>(m_attribute->hp) / m_attribute->hpmax;
}

inline std::string player::gethpandhpmax() const {
  return std::to_string(m_attribute->hp) + "/" +
         std::to_string(m_attribute->hpmax);
}

inline const float player::exppercent() const {
  return static_cast<float>(m_attribute->exp) / m_attribute->expnext;
}

inline std::string player::getexpandexpnext() const {
  return std::to_string(m_attribute->exp) + "/" +
         std::to_string(m_attribute->expnext);
}

inline const int &player::getlevel() const { return this->m_attribute->level; }

inline void player::losehp(const int &hp) {
  m_attribute->losehp(hp);
}
inline void player::gainhp(const int &hp) {
  m_attribute->gainhp(hp);
}
inline void player::loseexp(const int &exp) {
  m_attribute->loseexp(exp);
}
inline void player::gainexp(const int &exp) {
  m_attribute->gainexp(exp);
}

void player::updateanimation(const float &dt) {
  if (m_attacking) {

  }

  if (m_movment->getmovstate(movment_state::STAND)) {
    m_animation->play("IDEL", dt, 1.f, 1.f);
  } else if (m_movment->getmovstate(movment_state::MOVELEFT)) {
    m_animation->play("WALK_LEFT", dt, m_movment->getvalocity().x,
                      m_movment->getmaxvalocity());
  } else if (m_movment->getmovstate(movment_state::MOVERIGHT)) {
    m_animation->play("WALK_RIGHT", dt, m_movment->getvalocity().x,
                      m_movment->getmaxvalocity());
  } else if (m_movment->getmovstate(movment_state::MOVEUP)) {
    m_animation->play("WALK_UP", dt, m_movment->getvalocity().y,
                      m_movment->getmaxvalocity());
  } else if (m_movment->getmovstate(movment_state::MOVEDOWN)) {
    m_animation->play("WALK_DOWN", dt, m_movment->getvalocity().y,
                      m_movment->getmaxvalocity());
  }
}

void player::update(const float &dt,const sf::Vector2f& mouse_pos_view) {
  m_attribute->update();

  m_movment->update(dt);

  updateattack();

  updateanimation(dt);

  m_hitbox->update();

  m_sword.update(mouse_pos_view,this->getentitycenter ());
}

void player::render(sf::RenderTarget &target, sf::Shader *shader,
                    const bool &show_hitbox) {
  if (shader) {
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", this->getentitycenter());
  }

  target.draw(m_sprite, shader);
  m_sword.render(target,shader);

  if (show_hitbox)
    m_hitbox->render(target);
}