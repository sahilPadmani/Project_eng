#pragma once

#include "tile.h"
tile::tile(const int &x, const int &y, const float &gridsize,
           const sf::Texture &texture, const sf::IntRect &texture_rect,
           const bool collison, const short type) {
  m_tile.setSize(sf::Vector2f(gridsize, gridsize));
  // m_tile.setFillColor (sf::Color::White);
  // m_tile.setOutlineThickness (1.f);
  // m_tile.setOutlineColor (sf::Color::Black);
  m_tile.setPosition(static_cast<float>(x) * gridsize,
                     static_cast<float>(y) * gridsize);
  m_tile.setTexture(&texture);
  m_tile.setTextureRect(texture_rect);

  m_collision = collison;
  m_type = type;
}

tile::~tile() {}

void tile::update() {}
inline const short &tile::gettype() const { return m_type; }
inline const std::string tile::getstring() const {
  std::stringstream ss;

  ss << m_tile.getTextureRect().left << ' ' << m_tile.getTextureRect().top
     << ' ' << m_collision << ' ' << m_type;

  return ss.str();
}

inline const bool &tile::getcollison() const { return this->m_collision; }
inline const sf::Vector2f &tile::gettilepos() const { return m_tile.getPosition(); }

inline const sf::FloatRect tile::getglobalbound() const {
  return m_tile.getGlobalBounds();
}

inline const bool tile::intersects(const sf::FloatRect &entityglobalbound) const {
  return m_tile.getGlobalBounds().intersects(entityglobalbound);
}

void tile::render(sf::RenderTarget &target, const sf::Vector2f playerpos,
                  sf::Shader *shader) {

  if (shader) {
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", playerpos);
  }
  target.draw(m_tile, shader);
}
