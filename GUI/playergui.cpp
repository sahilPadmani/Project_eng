#pragma once

#include "playergui.h"

void playergui::initfont() {
  if (!m_font.loadFromFile("./resource/Font/main_manu_font.otf")) {
    throw("Error:- STATE::MAINMANUSTATE::intfont() Load font file falled.\n");
  }
}

void playergui::initlevel() {
  m_levelpos.x = gui::p2pX(1.04f, this->m_vm); // sf::Vector2f(20.f,20.f);
  m_levelpos.y = gui::p2pY(2.22f, this->m_vm);

  m_levelbarback.setSize(
      sf::Vector2f(gui::p2pX(2.08f, this->m_vm), gui::p2pY(4.44f, this->m_vm))
    );

  m_levelbarback.setFillColor(sf::Color(50, 50, 50, 200));
  m_levelbarback.setPosition(m_levelpos);

  m_leveltext.setFont(m_font);
  m_leveltext.setCharacterSize(gui::calccharsize(this->m_vm,95));
  m_leveltext.setPosition(m_levelpos.x + gui::p2pX(0.52f, this->m_vm), m_levelpos.y + gui::p2pY(0.26f, this->m_vm));
}

void playergui::inithpbar() {

  m_hpbar = new gui::progressbar( 1.04f , 8.88f , 15.625f , 4.44f , this->m_vm , &m_font);
  // m_hpbarback.setFillColor(sf::Color(50, 50, 50, 200));
  // m_hpbargreen.setFillColor(sf::Color::Green);
}

void playergui::initexpbar() {
  m_expbar = new gui::progressbar( 1.04f , 15.55f , 13.02f , 4.44f , this->m_vm , &m_font);
  
  // m_expbarback.setFillColor(sf::Color(50, 50, 50, 200));

  // m_expbargreen.setFillColor(sf::Color(250, 20, 20, 200));
}

playergui::playergui(player *player, sf::VideoMode &vm) : m_vm(vm) {
  m_player = player;
  initfont();
  initlevel();
  inithpbar();
  initexpbar();
}

playergui::~playergui() {
  delete m_hpbar;
  delete  m_expbar;
}

inline void playergui::updatelevel() {
  m_leveltext.setString(std::to_string(m_player->getlevel()));
}

inline void playergui::updateexpbar() {
  m_expbar->update(m_player->exppercent(), m_player->getexpandexpnext());
}

inline void playergui::updatehpbar() {
  m_hpbar->update(m_player->hppercent(),m_player->gethpandhpmax());
}

void playergui::update(const float &dt) {
  updatelevel();
  updatehpbar();
  updateexpbar();
}

inline void playergui::renderlevel(sf::RenderTarget &target) {
  target.draw(m_levelbarback);
  target.draw(m_leveltext);
}

void playergui::render(sf::RenderTarget &target) {
  renderlevel(target);
  m_expbar->render(target);
  m_hpbar->render(target);
}