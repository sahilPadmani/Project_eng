#pragma once

/**
 * The code defines a C++ class for an entity in a game, with functions to set sprite texture, create
 * hitbox, movement, animation components, set position, move, update, and render.
 */
#include "entity.h"

/**
 * The entity constructor initializes pointers to hitbox, movement, and animation objects to NULL.
 */
entity::entity(){
    m_hitbox = nullptr;
    m_movment = nullptr;
    m_animation = nullptr;
    m_skill = nullptr;
}

entity::~entity(){
    delete  m_hitbox;
    delete  m_movment;
    delete  m_animation;
    delete  m_attribute;
    delete m_skill;
}

inline void entity::setspritetexture(const sf::Texture& texture){
    m_sprite.setTexture(texture);
}


/**
 * The function creates a hitbox for an entity at a specified position with a specified height and
 * width.
 * 
 * @param x The `x` parameter represents the x-coordinate of the hitbox's position.
 * @param y The `y` parameter in the `createhitbox` function represents the vertical position of the
 * hitbox within the game world.
 * @param height The `height` parameter in the `createhitbox` function represents the vertical size of
 * the hitbox that is being created for the entity. It determines how tall the hitbox will be in the
 * game world.
 * @param width The `width` parameter in the `createhitbox` function represents the width of the hitbox
 * that is being created for the entity. It defines the horizontal extent or size of the hitbox in the
 * game world.
 */
inline void entity::createhitbox(const float& x ,const float& y,const float& height,const float& width){
    m_hitbox = new hitbox(m_sprite,x,y,height,width);
}

/**
 * The function creates a movement object with specified maximum velocity, acceleration, and
 * deceleration for an entity.
 * 
 * @param maxvalocity The `maxvalocity` parameter represents the maximum velocity that the entity can
 * reach during movement. This value determines the upper limit of how fast the entity can move.
 * @param acceleration Acceleration is the rate at which the velocity of the entity changes over time.
 * It determines how quickly the entity can increase its speed.
 * @param deceleration Deceleration refers to the rate at which an object slows down or comes to a
 * stop. It is the opposite of acceleration, and it is usually represented as a negative value to
 * indicate the decrease in velocity over time. In the context of your code snippet, the deceleration
 * parameter is likely used
 */
inline void entity::createmovment(const float& maxvalocity , const float& acceleration ,const float& deceleration){
    m_movment = new movment(m_sprite,maxvalocity,acceleration,deceleration);
}

inline void entity::createanimation(sf::Texture& texture){
    m_animation = new animationcomponent(m_sprite ,texture);
}

inline void entity::createattribute(const unsigned& level){
    m_attribute = new attributecomponet(level);
}

inline void entity::createatskill(){
    m_skill = new skillcomponet();
}

inline void entity::setposition(const float& x,const float& y){
    m_hitbox ? m_hitbox->setpos(sf::Vector2f(x,y)) : m_sprite.setPosition (x,y);
}

inline void entity::move(const float& dt,const float& dir_x,const float& dir_y){
    if(m_movment)
        m_movment->move(dt,dir_x, dir_y);
    
    if (m_skill) 
        m_skill->gainexp(SKILLS::ENDURANCE,1);
}
inline void entity::stopvelocity(){
    if(m_movment)
    m_movment->stopvelocity();
}

inline void entity::stopvelocityX(){
    if(m_movment)
    m_movment->stopvelocityX();
}

inline void entity::stopvelocityY(){
    if(m_movment)
    m_movment->stopvelocityY();
}

inline const sf::Vector2f& entity::getentitypos()const{
     return  m_hitbox ? m_hitbox->getpos() :  m_sprite.getPosition ();
}
inline const sf::Vector2f entity::getentitycenter() const {
    if (m_hitbox) {
        return m_hitbox->getpos() + sf::Vector2f(m_hitbox->getglobalbound().width, m_hitbox->getglobalbound().height) / 2.f;
    } else {
        return m_sprite.getPosition() + sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height) / 2.f;
    }
}


inline const sf::FloatRect entity::getglobalbound()const{
    return m_hitbox ? m_hitbox->getglobalbound() :m_sprite.getGlobalBounds();
}

inline const sf::Vector2i entity::getgridpos(const int& gridsize)const{
    sf::Vector2f pos = m_hitbox ? m_hitbox->getpos() : m_sprite.getPosition();

return sf::Vector2i(
    static_cast<int>(pos.x) / gridsize,
    static_cast<int>(pos.y) / gridsize
);
}

inline const sf::FloatRect entity::getnextbound(const float& dt)const{
    return (m_movment && m_hitbox) ? this->m_hitbox->getnextpos(m_movment->getvalocity() * dt) : sf::FloatRect(-1.f,-1.f,-1.f,-1.f) ;
}


// void entity::update(const float& dt){
// }

// void entity::render(sf::RenderTarget& target){
    
// }