#pragma once

#include "../header/movment.h"

movment::movment(sf::Sprite& sprite , const float& valocity , const float&  acceleration ,const float& deceleration)
:m_sprite(sprite),m_maxvalocity(valocity),m_acceleration(acceleration),m_deceleration(deceleration){
}

movment::~movment(){

}


inline void movment::stopvelocity(){
    stopvelocityX();
    stopvelocityY();
}

inline void movment::stopvelocityX(){
    m_valocity.x = 0.f;
}

inline void movment::stopvelocityY(){
    m_valocity.y = 0.f;
}

inline const float& movment::getmaxvalocity() const{
    return this->m_maxvalocity;
}

inline const sf::Vector2f& movment::getvalocity() const{
    return this->m_valocity;
}


inline const bool movment::getmovstate(const short& state)const{
    bool value ;
    switch (state) {
        case movment_state::STAND:
            value = (m_valocity.x == 0.f && m_valocity.y == 0.f);
        break;
        case  movment_state::MOVELEFT:
            value = (m_valocity.x < 0.f );
        break;
        case  movment_state::MOVERIGHT:
            value = (m_valocity.x > 0.f);
        break;
        case  movment_state::MOVEUP:
            value = (m_valocity.y < 0.f);
        break;
        case  movment_state::MOVEDOWN:
            value = (m_valocity.y > 0.f);
        break;
    }
    return value;
}

inline void movment::move(const float& dt,const float& dir_x , const float& dir_y){
    m_valocity.x += m_acceleration * dir_x * dt;
    m_valocity.y += m_acceleration * dir_y *dt; 
}

void movment::update(const float& dt){
    // for x
    if(m_valocity.x > 0.f){

        // acceleration
        if(m_valocity.x > m_maxvalocity)
            m_valocity.x = m_maxvalocity;

        // deceleration
        m_valocity.x -= m_deceleration * dt;
        if(m_valocity.x < 0.f)
            m_valocity.x = 0.f;

    }else if(m_valocity.x < 0.f) {

        // acceleration
        if(m_valocity.x < -m_maxvalocity)
            m_valocity.x = -m_maxvalocity;

        // deceleration
        m_valocity.x += m_deceleration * dt;
        if(m_valocity.x > 0.f)
            m_valocity.x = 0.f;
    }

    // for y
    if(m_valocity.y > 0.f){

        // acceleration
        if(m_valocity.y > m_maxvalocity)
            m_valocity.y = m_maxvalocity;

        // deceleration
        m_valocity.y -= m_deceleration * dt;
        if(m_valocity.y < 0.f)
            m_valocity.y = 0.f;

    }else if(m_valocity.y < 0.f) {

        // acceleration
        if(m_valocity.y < -m_maxvalocity)
            m_valocity.y = -m_maxvalocity;

        // deceleration
        m_valocity.y += m_deceleration * dt;
        if(m_valocity.y > 0.f)
            m_valocity.y = 0.f;
    }

    //final move
    m_sprite.move (m_valocity * dt);
}