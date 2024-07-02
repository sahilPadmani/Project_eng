#pragma once

#include "tile.cpp"
#include "../entity/entity.cpp"

class tile;

class entity;

class tilemap{

    float m_gridsizef;
    int m_gridsizei;
    int m_layers;
    sf::Vector2i m_maxgridsize;
    sf::Vector2f m_maxmapsize;
    std::vector<std::vector<std::vector<std::vector<tile*>>>> m_map;
    std::string m_texturefilepath;
    sf::Texture m_tilesheet;

    std::stack<tile*> m_deferredrenderstack;

    sf::RectangleShape m_collisionbox;


    int m_fromx;
    int m_tox;
    int m_fromy;
    int m_toy;
    int m_tolayer;
    void clearmap();
    void resizemap();

    inline void inittexture();
    inline void initcollisionbox();
    
    public:
    tilemap(const float& griedsize ,const int& h ,const int& w,const std::string_view& texturefilepath);
    tilemap(const std::string& file_name);
    virtual ~tilemap();

    //acess
    inline const bool gettileisaddon(const int& x, const int& y,const int& z)const;
    inline const sf::Texture* gettilesheet()const;
    inline const int getlayersize(const int& grid_x,const int& grid_y,const int& layer)const;
    inline const sf::Vector2f& getmaxsize()const;
    inline const sf::Vector2i& getmaxgrid()const;
    
    inline void addtile(const int& x, const int& y,const int& z,const sf::IntRect& texture_rect , const bool& collision,const short& type);
    inline void removetile(const int& x, const int& y,const int& z);

    void update();

    void renderfullmap(sf::RenderTarget& target);
    void render(sf::RenderTarget& target,
                const sf::Vector2i& entitygridpos,const sf::Vector2f playerpos = sf::Vector2f(),
                sf::Shader* shader = nullptr,const bool &show_collison = false);
    void deferredrender(sf::RenderTarget& target,const sf::Vector2f& playerpos = sf::Vector2f(),sf::Shader* shader = nullptr);

    void savemapfile(const std::string_view filename);
    void loadmapfile(const std::string_view filename);

    inline void activegrid(const sf::Vector2i& gridpos);
    inline void fourtilecollision(entity &entity,const sf::FloatRect& playerbound,const sf::FloatRect& wallbound);
    void updatecollision(entity& entity,const float& dt);
};