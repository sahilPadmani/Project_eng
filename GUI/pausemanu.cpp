#pragma once

#include "pausemanu.h"

pausemanu::pausemanu(const sf::VideoMode& vm, sf::Font &font) : m_font(font) {
  m_background.setSize(
      sf::Vector2f(
        static_cast<float>(vm.width),
        static_cast<float>(vm.height)
      )
    );

  m_background.setFillColor(sf::Color(20, 20, 20, 100));

  m_container.setSize(
      sf::Vector2f(static_cast<float>(vm.width) / 4.f,
                   static_cast<float>(vm.height) - gui::p2pY(6.66f,vm))
        );
  m_container.setFillColor(sf::Color(20, 20, 20, 200));

  m_container.setPosition(
      static_cast<float>((vm.width - m_container.getSize().x) / 2.f),
      30.f
    );

  m_text.setFont(m_font);
  m_text.setFillColor(sf::Color(255, 255, 255, 200));
  m_text.setCharacterSize(gui::calccharsize(vm));
  m_text.setString("Pause Manu");
  m_text.setPosition(
      m_container.getPosition().x +
          (m_container.getSize().x - m_text.getGlobalBounds().width) / 2.f,
      m_container.getPosition().y + gui::p2pY( 1.11f,vm)
    );
}

pausemanu::~pausemanu() {
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    delete i.second;
  }
}

void pausemanu::addbutten(const std::string &key, const float &y,
                          const float &w, const float &h,
                          const unsigned &charsize, const std::string &text) {

//   float w = 250.f;
//   float h = 50.f;

  float x = m_container.getPosition().x + (m_container.getSize().x - w) / 2.f;

  m_butten[key] =
      new gui::butten(x, y, w, h, m_font, text, charsize,
                      sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250),
                      sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0),
                      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

inline std::map<std::string, gui::butten *> &pausemanu::getbutten() {
  return this->m_butten;
}

inline const bool pausemanu::isbuttenpressed(const std::string &key) {
  return m_butten[key]->ispressed();
}

void pausemanu::update(const sf::Vector2i &mouspos) {
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    i.second->update(mouspos);
  }
}

void pausemanu::render(sf::RenderTarget &target) {
  target.draw(m_background);
  target.draw(m_container);

  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    i.second->render(target);
  }

  target.draw(m_text);
}