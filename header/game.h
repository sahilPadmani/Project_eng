#pragma once

#include "../source/clock.cpp"
#include "../state/mainmanustate.cpp"
#include "../source/graphicsettings.cpp"

class mainmanustate;
class graphicssettings;
class clocktimer;

class game {

  graphicssettings m_gfsetting;
  statedata m_statedata;

  sf::RenderWindow *m_window;
  sf::Event m_event;

  sf::Clock m_dtclock;
  float m_dt;

  std::stack<state *> m_states;
  std::map<std::string, int> m_supportedkeys;

  float m_gridsize;

  inline void initvar();
  inline void initgfsetting();
  inline void initwindow();
  inline void initstatedata();
  inline void initstates();
  void initkeys();

public:
  game();
  virtual ~game();

  inline void endapplication();

  inline void update_dt();
  void update_pollevent();
  void update();

  inline void render();

  void run();
};