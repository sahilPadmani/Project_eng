#pragma once

#include "state.cpp"
#include "../GUI/gui.cpp"

class state;
class butten;

class settingstate : public state {
private:
  graphicssettings& m_gfsetting;

  sf::Texture m_backgroundtexture;
  sf::RectangleShape m_background;

  std::map<std::string,gui::butten *> m_butten;
  std::map<std::string,gui::dropdownlist*> m_dropdownlist;

  clocktimer m_timerdropdownlist;
  bool m_dropdownhelper;
  sf::Text m_optionstext;
  std::vector<sf::VideoMode> m_modes;
  std::vector<std::string> m_modes_str;
  int m_activemode;

  void initvar();
  inline void initbackground();
  inline void initfont();
  void initkeybinds();
  void initgui();

  void cleanupgui();

public:
  settingstate(statedata& data);
  virtual ~settingstate();
  void resetgui();

  inline void updateinput(const float &dt);
  void updategui();
  inline void update(const float &dt);

  void rendergui(sf::RenderTarget &target);
  inline void render(sf::RenderTarget *target);
};