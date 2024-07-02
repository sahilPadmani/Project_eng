#pragma once

#include "../preheader.hpp"

enum tiletype{DEFALUT = 0 , DAMAGING , POSTDRAW};

class tile{
private:
    sf::RectangleShape m_tile;
    bool m_collision;
    short m_type;

public:
tile(const int& x, const int& y , const float& gridsize,const sf::Texture& texture,const sf::IntRect& texture_rect,const bool collison = false ,const short type  =  tiletype::DEFALUT);
virtual ~tile();

inline const bool& getcollison()const;
inline const short& gettype()const;
inline const std::string getstring()const;
inline const sf::Vector2f& gettilepos()const;
inline const sf::FloatRect getglobalbound()const;
inline const bool intersects(const sf::FloatRect& entityglobalbound)const;

void update();
void render(sf::RenderTarget& target,const sf::Vector2f playerpos = sf::Vector2f() ,sf::Shader* shader = nullptr);

};