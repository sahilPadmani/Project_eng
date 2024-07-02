#pragma once

#include "gui.cpp"
class player;
class playergui
{
private:
    player* m_player;
    sf::VideoMode& m_vm;
    sf::Font m_font;

    //level
    sf::Vector2f m_levelpos;
    sf::Text m_leveltext;
    sf::RectangleShape m_levelbarback;

    //exp bar
    gui::progressbar* m_expbar;

    //hp bar
    gui::progressbar* m_hpbar;

    void initlevel();
    void initfont();
    void initexpbar();
    void inithpbar();

public:
    playergui(player* player,sf::VideoMode& vm);
    virtual ~playergui();

    inline void updatelevel();
    inline void updateexpbar();
    inline void updatehpbar();
    void update(const float& dt);

    inline void renderlevel(sf::RenderTarget& target);
    void render(sf::RenderTarget& target);
};
