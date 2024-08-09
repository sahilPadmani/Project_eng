#pragma once

#include "../header/game.h"

inline void game::initvar() { m_gridsize = 64.f; }

inline void game::initgfsetting() {
  m_gfsetting.loadfromfile("./resource/winconfig.ini");
}

inline void game::initwindow() {
  sf::Uint32 ui = sf::Style::Fullscreen;

  if (!m_gfsetting.fullscreen)
    ui = sf::Style::Close | sf::Style::Titlebar;

  m_window = new sf::RenderWindow(m_gfsetting.resolution, m_gfsetting.title, ui,
                                  m_gfsetting.contextsettings);
  m_window->setFramerateLimit(m_gfsetting.Framrate);
  m_window->setVerticalSyncEnabled(m_gfsetting.vecSync);
}

inline void game::initstatedata() {
  m_statedata.gridsize = m_gridsize;
  m_statedata.window = m_window;
  m_statedata.gfsettings = &m_gfsetting;
  m_statedata.supportedkeys = &m_supportedkeys;
  m_statedata.states = &m_states;
  m_statedata.state_type = State_Type::MAIN_MANU;
}

inline void game::initstates() {
  m_states.push(new mainmanustate(m_statedata));
}

void game::initkeys() {

  std::ifstream ifs("./resource/keyconfig.ini");

  if (ifs.is_open()) {
    std::string key;
    int value;

    while (ifs >> key >> value) {
      m_supportedkeys[key] = value;
    }
  }
  ifs.close();
}

inline void game::update_dt() { m_dt = m_dtclock.restart().asSeconds(); }

void game::update_pollevent() {
  while (m_window->pollEvent(m_event)) {
    if (m_event.type == sf::Event::Closed)
      m_window->close();
  }
}

game::game() {
  this->initvar();
  this->initgfsetting();
  this->initwindow();
  this->initkeys();
  this->initstatedata();
  this->initstates();
}
game::~game() {
  delete m_window;

  while (!m_states.empty()) {
    delete m_states.top();
    m_states.pop();
  }
}

// public funciton

void game::run() {
#ifdef FIND
  std::cout<<"What game play(BGMI)?.\n";
#else
  while (m_window->isOpen()) {
    update_dt();
    update();
    render();

#ifdef MEMORY_CHECK
    system("cls");
    std::cout << "Memory use by one frame: " << memory.memoryInUse()
              << " Bytes.\n";
#endif
  }
#endif
}

void game::update() {

  update_pollevent();

  if (!m_window->hasFocus()) {
    return;
  }

  if (m_states.empty()) {
    endapplication();
    m_window->close();
    return;
  }

  m_states.top()->update(m_dt);

  if (m_states.top()->getQuit()) {
    m_states.top()->endstate();
    delete m_states.top();
    m_states.pop();
  }
}

inline void game::render() {
  m_window->clear();

  if (m_window->hasFocus()) {
    if (!m_states.empty())
      m_states.top()->render(m_window);
  }
  m_window->display();
}

inline void game::endapplication() { std::cout << "END Application.\n"; }