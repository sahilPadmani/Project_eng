#pragma once

#include "meleeweapon.cpp"

class meleeweapon;
class sword : public meleeweapon
{
private:

public:
    sword();
    virtual ~sword(); 

    // Members
    void update(const sf::Vector2f& mouseview,const sf::Vector2f& center);
    void render(sf::RenderTarget& target,const sf::Shader* shader = nullptr);
};
