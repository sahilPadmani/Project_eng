#pragma once

#include "../preheader.hpp"

#include "gui.cpp"


class butten;

class pausemanu{
    sf::Font& m_font;
    sf::Text m_text;

    sf::RectangleShape m_background;
    sf::RectangleShape m_container;

    std::map<std::string,gui::butten*> m_butten;

public:
pausemanu(const sf::VideoMode& vm,sf::Font& font);
virtual ~pausemanu();

    inline std::map<std::string,gui::butten*>& getbutten();
    inline const bool isbuttenpressed(const std::string& key);

    void addbutten(const std::string &key, const float &y,
                          const float &w, const float &h,
                          const unsigned &charsize, const std::string &text);
    void update(const sf::Vector2i& mousepos);
    void render(sf::RenderTarget& target);

};