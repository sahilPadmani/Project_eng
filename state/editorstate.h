#pragma once

#include "state.cpp"
#include "../GUI/gui.cpp"
#include "../GUI/pausemanu.cpp"
#include "../tilemap/tilemap.cpp"

class state;
class butten;
class pausemanu;
class tilemap;

class editorstate : public state{

  sf::View m_view;
  float m_viewspeed;
  
  clocktimer m_timelimitforselector;
  clocktimer m_keypress;
  bool m_keypresshelper;
  bool m_onetime;
  bool m_addtilelock;
  bool m_selectorhelper;

  sf::Font m_font;
  sf::Text m_cursortext;
  pausemanu* m_pmanu;

  bool m_collision;
  short m_type;
  int m_layer;

  sf::Vector2i m_lastselectorgrid;

  tilemap* m_map;
  gui::textureselector* m_textureselector; 
  sf::IntRect m_texturerect;
  sf::RectangleShape m_siderbar;

  std::map<std::string , gui::butten*> m_butten;

  inline void initvar();
  inline void initview();
  inline void initbackground();
  inline void initfont();
  inline void inittext();
  void initkeybinds();
  inline void initgui();
  inline void initpause();
  inline void initselector();
  inline void inittilemap();

public:
  editorstate(statedata& data);
  virtual ~editorstate();

  inline void updateview(const float& dt);
  void updateinput(const float& dt);
  void updateeditinput(const float& dt);
  void updategui();
  inline void updatepausemanuinput();
  inline void updateselector();
  void update(const float& dt);

  void rendergui(sf::RenderTarget& target);
  inline void renderselector(sf::RenderTarget& target);
  void render(sf::RenderTarget* target);
};