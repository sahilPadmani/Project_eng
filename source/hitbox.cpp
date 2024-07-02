#pragma once

#include "../header/hitbox.h"

hitbox::hitbox(sf::Sprite& sprite,
        const float& x ,const float& y,const float& height,const float& width):m_sprite(sprite),m_offsetx(x),m_offsety(y){
    m_nextposition.left = 0.f;
    m_nextposition.top  = 0.f;
    m_nextposition.width = width;
    m_nextposition.height = height;


    m_hitbox.setPosition (m_sprite.getPosition ().x + m_offsetx , m_sprite.getPosition ().y + m_offsety);
    m_hitbox.setSize(sf::Vector2f(width,height));
    m_hitbox.setFillColor (sf::Color::Transparent);
    m_hitbox.setOutlineThickness (-1.f);
    m_hitbox.setOutlineColor (sf::Color::Green);
}

hitbox::~hitbox(){}


inline const sf::Vector2f& hitbox::getpos()const{
    return m_hitbox.getPosition ();
}

inline void hitbox::setpos(const sf::Vector2f& pos){
    m_hitbox.setPosition (pos);
    m_sprite.setPosition (pos.x - m_offsetx , pos.y - m_offsety);
}

inline const bool hitbox::checkintersect(const sf::FloatRect& frect) const{
    return m_hitbox.getGlobalBounds ().intersects(frect);
}

inline const sf::FloatRect hitbox::getglobalbound()const{
    return m_hitbox.getGlobalBounds ();
}

inline const sf::FloatRect& hitbox::getnextpos(const sf::Vector2f& valocity){
    m_nextposition.left = m_hitbox.getPosition ().x + valocity.x;
    m_nextposition.top = m_hitbox.getPosition ().y + valocity.y;
    return m_nextposition;
}

inline void hitbox::update(){
    m_hitbox.setPosition (m_sprite.getPosition ().x + m_offsetx , m_sprite.getPosition ().y + m_offsety);
}

inline void hitbox::render(sf::RenderTarget& target){
    target.draw(m_hitbox);
}