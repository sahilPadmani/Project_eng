#pragma once
#include "sword.h"
sword::sword() {
  if (!p_texture.loadFromFile("./resource/sprites/player/sword.png")) {
    std::cout
        << "Error: GAMESTATE::PLAYER class() falled to load sword texture.\n";
  } else {
    p_sprite.setTexture(p_texture);
    p_sprite.setOrigin(p_sprite.getGlobalBounds().width / 2.f,
                       p_sprite.getGlobalBounds().height);
  }
}

sword::~sword() {
  // TODO: Needs implementation
}


void sword::update(const sf::Vector2f& mouseview,const sf::Vector2f& center){

 p_sprite.setPosition (center);
  static float dx;
  static float dy;
    dx = mouseview.x -  this->p_sprite.getPosition().x;
    dy = mouseview.y - this->p_sprite.getPosition ().y;

  static float deg;
    deg = atan2f(dy,dx) * 180 / M_PI ;

    p_sprite.setRotation (deg + 90.f);
  
}

void sword::render(sf::RenderTarget& target,const sf::Shader* shader){
    target.draw(p_sprite,shader);
}