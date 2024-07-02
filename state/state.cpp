#pragma once

#include "state.h"

state::state(statedata& data):m_statedata(data){

    this->m_gridsize = data.gridsize;
    this->m_window = data.window;
    this->m_supportedkeys = data.supportedkeys;
    this->m_states = data.states;

    this->m_Quit = false;
    this->m_pause = false;

    this->m_keytime = 0.f;
    this->m_keytimemax = 10.f;
}

state::~state(){
    
}

inline const bool& state::getQuit() const{
    return this->m_Quit;
}

inline const bool state::getkey(){
    if(m_keytime >= m_keytimemax){
        m_keytime = 0.f;
        return true;
    }
    return true;
}



inline void state::endstate(){
    m_Quit = true;
}

inline void state::pausestate(){
    m_pause = true;
}

inline void state::unpausestate(){
    m_pause = false;
}

inline void state::updatemousepos(sf::View* view){
    m_mouseposscreen = sf::Mouse::getPosition();
    m_mouseposwindow = sf::Mouse::getPosition(*m_window);

    if(view)
        m_window->setView (*view);

    m_mouseposview = m_window->mapPixelToCoords (sf::Mouse::getPosition(*m_window));
    m_mouseposgrid = sf::Vector2i(
        static_cast<int>(m_mouseposview.x / m_gridsize) ,
        static_cast<int>(m_mouseposview.y / m_gridsize)
    );

    m_window->setView (m_window->getDefaultView ());
}

inline void state::updatekeytime(const float& dt){
    if (m_keytime < m_keytimemax) {
        m_keytime += 100.f * dt;
    }
}