#pragma once

#include "gamestate.cpp"
#include "editorstate.cpp"
#include "settingstate.cpp"
#include "../GUI/gui.cpp"

class gamestate;
class editorstate;
class settingstate;
class butten;


class mainmanustate : public state {
private:
  graphicssettings& m_gfsetting;
  sf::Texture m_backgroundtexture;
  sf::RectangleShape m_background;
  // sf::Font m_font;

  std::map<std::string , gui::butten*> m_butten;

  inline void initbackground();
  inline void initfont();
  void initkeybinds();
  void initgui();

  void cleanupgui();

public:
  mainmanustate(statedata& data);
  virtual ~mainmanustate();
  void resetgui();

  inline void updateinput(const float& dt);
  void updategui();
  inline void update(const float& dt);

  void rendergui(sf::RenderTarget& target);
  inline void render(sf::RenderTarget* target);
};