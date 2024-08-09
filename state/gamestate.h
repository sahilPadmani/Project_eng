#pragma once

#include "state.cpp"
#include "../GUI/pausemanu.cpp"
#include "../tilemap/tilemap.cpp"
#include "../GUI/playergui.cpp"
#include "../item/meleeweapon/sword.cpp"
#include "../item/rangeweapon/bow.cpp"

class state;
class player;
class pausemanu;
class tilemap;
class playergui;
class sword;
class bow;

class gamestate : public state{
private:
  sf::View m_view;
  sf::Vector2i m_viewgridpos;
  sf::RenderTexture m_rendertexture;
  sf::Sprite m_rendersprite;

  sf::Shader m_core_sheder;

  pausemanu* m_pmanu;
  tilemap* m_map;
  player* m_player;
  playergui* m_playergui;
  bool m_onetime;

  inline void initdeferredrender();
  inline void initview();
  void initkeybinds();
  inline void initfont();
  inline void inittexture();
  inline void initshader();
  inline void initpause();
  inline void initplayer();
  inline void initplayergui();
  inline void inittilemap();

  void cleanupgui();
  
public:
  gamestate(statedata& data);
  virtual ~gamestate();
  void resetgui();

  void updateinput(const float& dt);
  inline void updateplayerinput(const float& dt);
  inline void updateplayergui(const float& dt);
  void updateview();
  inline void updategui();
  inline void updatemap(const float& dt);
  void update(const float& dt);

  void render(sf::RenderTarget* target);
};