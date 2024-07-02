#pragma once

#include "../preheader.hpp"

class hitbox{
    sf::Sprite& m_sprite;
    sf::RectangleShape m_hitbox;
    sf::FloatRect m_nextposition;

    float m_offsetx;
    float m_offsety;

public:
hitbox(sf::Sprite& sprite,
        const float& x ,const float& y,const float& height,const float& width);
virtual ~hitbox();


    inline const sf::Vector2f& getpos()const;
    inline const sf::FloatRect getglobalbound()const;
    inline const sf::FloatRect& getnextpos(const sf::Vector2f& addvalue);

    inline void setpos(const sf::Vector2f& pos);

    inline const bool checkintersect(const sf::FloatRect& frect) const;

    inline void update();
    inline void render(sf::RenderTarget& target);
};