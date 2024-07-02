#pragma once

#include "../entity/player.cpp"
#include "../source/graphicsettings.cpp"

class player;
class graphicssettings;
class state;

struct statedata{
    float gridsize;
    sf::RenderWindow* window;
    graphicssettings* gfsettings;
    std::map<std::string,int>* supportedkeys;
    std::stack<state*>* states;
};

class state{

protected:
    statedata& m_statedata;
    sf::Font m_font;
    std::stack<state*>* m_states;

    sf::RenderWindow* m_window;


    float m_gridsize;
    std::map<std::string,int>* m_supportedkeys;
    std::map<std::string,int> m_keybinds;
    bool m_Quit;
    bool m_pause;
    
    float m_keytime;
    float m_keytimemax;

    sf::Vector2i m_mouseposscreen;
    sf::Vector2i m_mouseposwindow;
    sf::Vector2f m_mouseposview;
    sf::Vector2i m_mouseposgrid;

    std::map<std::string,sf::Texture> m_texture;

    virtual void initkeybinds() = 0;
    virtual void initfont() = 0;

public:
    state(statedata&  data);
    virtual ~state();

    inline const bool& getQuit() const; 
    inline const bool getkey();

    inline void endstate();
    inline void pausestate();
    inline void unpausestate();

    virtual inline void updatemousepos(sf::View* view = nullptr);
    virtual inline void updatekeytime(const float& dt);
    virtual void updateinput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = NULL) = 0;

};