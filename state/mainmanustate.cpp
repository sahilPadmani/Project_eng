#pragma once

#include "mainmanustate.h"

inline void mainmanustate::initbackground() {
  // m_backgorund.setFillColor (sf::Color::Magenta);

  m_background.setSize(static_cast<sf::Vector2f>(m_window->getSize()));

  if (!m_backgroundtexture.loadFromFile("./resource/background/main_manu.jpg"))
    throw(
        "Error:- STATE::MAINSTATE::intbackground falled to Load background.\n");

  m_background.setTexture(&m_backgroundtexture);
}

inline void mainmanustate::initfont() {
  if (!m_font.loadFromFile("./resource/Font/main_manu_font.otf")) {
    throw("Error:- STATE::MAINMANUSTATE::intfont() Load font file falled.\n");
  }
}

void mainmanustate::initkeybinds() {

  std::ifstream ifs("./resource/mainmanukey.ini");

  if (ifs.is_open()) {

    std::string key = "";
    std::string key2 = "";

    while (ifs >> key >> key2) {
      m_keybinds[key] = m_supportedkeys->at(key2);
    }
  }
  ifs.close();
}

void mainmanustate::initgui() {

  const sf::VideoMode& vm = this->m_statedata.gfsettings->resolution; 
  unsigned charsize = gui::calccharsize(vm);
  float width = gui::p2pX(13.02f,vm);
  float hight = gui::p2pY(5.55f,vm);

  m_butten["START_GAME"] = new gui::butten(
      gui::p2pX(43.75f,vm), gui::p2pY(60.f,vm), width, hight , m_font, "Start Game", charsize,
      sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250),
      sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

  m_butten["SETTINGS"] = new gui::butten(
      gui::p2pX(43.75f,vm), gui::p2pY(67.22f,vm), width, hight, m_font, "Settings", charsize,
      sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250),
      sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

  m_butten["EDITOR"] = new gui::butten(
      gui::p2pX(43.75f,vm), gui::p2pY(74.44f,vm), width, hight, m_font, "Editor", charsize,
      sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250),
      sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

  m_butten["QUIT"] = new gui::butten(
      gui::p2pX(43.75f,vm), gui::p2pY(81.66f,vm), width, hight, m_font, "Quit", charsize,
      sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250),
      sf::Color(20, 20, 20, 50), sf::Color(100, 100, 100, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}



mainmanustate::mainmanustate(statedata &data)
    : state(data), m_gfsetting(*data.gfsettings) {
  initbackground();

  initfont();

  initkeybinds();

  initgui();
}

mainmanustate::~mainmanustate() {
  this->cleanupgui();
}

void mainmanustate::cleanupgui (){
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    delete i.second;
  }
}

void mainmanustate::resetgui (){
  this->cleanupgui();
  
  m_butten.clear();

  initgui();
}

inline void mainmanustate::updateinput(const float &dt) {}

void mainmanustate::updategui() {
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    i.second->update(m_mouseposwindow);
  }

  if (m_butten["START_GAME"]->ispressed()) {
    m_statedata.state_type = State_Type::GAME;
    m_states->push(new gamestate(m_statedata));
  }

  if (m_butten["SETTINGS"]->ispressed()) {
    m_statedata.state_type = State_Type::SETTING;
    m_states->push(new settingstate(m_statedata));
  }

  if (m_butten["EDITOR"]->ispressed()) {
    m_statedata.state_type = State_Type::EDITOR;
    m_states->push(new editorstate(m_statedata));
  }

  if (m_butten["QUIT"]->ispressed()) {
    endstate();
  }
}

inline void mainmanustate::update(const float &dt) {

  // if(m_statedata.update_setting){
  //   resetgui();
  //   m_statedata.update_setting = false;
  // }

  updatemousepos();

  updateinput(dt);

  updategui();
}

void mainmanustate::rendergui(sf::RenderTarget &target) {
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    i.second->render(target);
  }
}

inline void mainmanustate::render(sf::RenderTarget *target) {
  if (!target)
    target = m_window;

  target->draw(m_background);

  rendergui(*target);

  // sf::Text mouse;
  // mouse.setCharacterSize(18);
  // std::stringstream ss;
  // ss<<m_mouseposview.x <<" " <<m_mouseposview.y;
  // mouse.setFont(m_font);
  // mouse.setString(ss.str());
  // mouse.setPosition(m_mouseposview.x ,m_mouseposview.y - 12);
  // target->draw(mouse);
}