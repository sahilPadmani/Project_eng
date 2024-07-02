#pragma once

#include "gamestate.h"

inline void gamestate::initdeferredrender() {
  m_rendertexture.create(m_statedata.gfsettings->resolution.width,
                         m_statedata.gfsettings->resolution.height);
  m_rendersprite.setTexture(m_rendertexture.getTexture());
  m_rendersprite.setTextureRect(
      sf::IntRect(0, 0, m_statedata.gfsettings->resolution.width,
                  m_statedata.gfsettings->resolution.height));
}
inline void gamestate::initview() {
  m_view.setSize(sf::Vector2f(m_statedata.gfsettings->resolution.width,
                              m_statedata.gfsettings->resolution.height));
  m_view.setCenter(sf::Vector2f(m_view.getSize() / 2.f));
}
void gamestate::initkeybinds() {

  std::ifstream ifs("./resource/gamekeybind.ini");

  if (ifs.is_open()) {

    std::string key = "";
    std::string key2 = "";

    while (ifs >> key >> key2) {
      m_keybinds[key] = m_supportedkeys->at(key2);
    }
  }
  ifs.close();
}

inline void gamestate::initfont() {
  if (!m_font.loadFromFile("./resource/Font/main_manu_font.otf")) {
    throw("Error:- STATE::MAINMANUSTATE::intfont() Load font file falled.\n");
  }
}

inline void gamestate::inittexture() {
  if (!m_texture["PLAYER_SHEET"].loadFromFile(
          "./resource/sprites/player/player_sheet2.png")) {
    throw("Error:- STATE::GAMESTATE:: inttexture falled to load player "
          "sprite.\n");
  }
}

inline void gamestate::initshader (){
  #ifdef SHADER_PACK
  if(!m_core_sheder.loadFromFile("./resource/shader/vertax_gamestate.vert","./resource/shader/fragment_gamestate.frag")){
    std::cout<<"Error:: GAMESTATE::initshader falled to load shader.\n";
  }
  #endif
}

inline void gamestate::initpause() {
  const sf::VideoMode &vm = this->m_statedata.gfsettings->resolution;
  m_pmanu = new pausemanu(vm, m_font);

  float w = gui::p2pX(13.02f, vm);
  float h = gui::p2pY(5.55f, vm);
  unsigned charsize = gui::calccharsize(vm);
  
  m_pmanu->addbutten("QUIT",gui::p2pY(44.44f,vm),w,h,charsize,"Quit");
}

inline void gamestate::initplayer() {
  m_player = new player(200, 200, m_texture["PLAYER_SHEET"]);
}

inline void gamestate::initplayergui() { m_playergui = new playergui(m_player,this->m_statedata.gfsettings->resolution); }

inline void gamestate::inittilemap() {
  m_map = new tilemap("map.slmp");
}

gamestate::gamestate(statedata &data) : state(data) {
  m_onetime = true;
  initdeferredrender();
  initview();
  initkeybinds();
  initfont();
  inittexture();
  initshader();
  initplayer();
  initplayergui();
  inittilemap();
  initpause();
}

gamestate::~gamestate() {
  delete m_map;
  delete m_player;
  delete m_pmanu;
  delete m_playergui;
}

void gamestate::updateview() {
  m_view.setCenter(
    std::floor(m_player->getentitypos().x + (static_cast<float>(m_mouseposwindow.x) - static_cast<float>( m_statedata.gfsettings->resolution.width)/2.f)/10.f),
    std::floor(m_player->getentitypos().y + (static_cast<float>(m_mouseposwindow.y) - static_cast<float>( m_statedata.gfsettings->resolution.height)/2.f)/10.f)
  );

  if (this->m_map->getmaxsize().x >= this->m_view.getSize().x)
	{
		if (this->m_view.getCenter().x - this->m_view.getSize().x / 2.f < 0.f)
		{
			this->m_view.setCenter(0.f + this->m_view.getSize().x / 2.f, this->m_view.getCenter().y);
		}
		else if (this->m_view.getCenter().x + this->m_view.getSize().x / 2.f > this->m_map->getmaxsize().x)
		{
			this->m_view.setCenter(this->m_map->getmaxsize().x - this->m_view.getSize().x / 2.f, this->m_view.getCenter().y);
		}
	}

	if (this->m_map->getmaxsize().y >= this->m_view.getSize().y)
	{
		if (this->m_view.getCenter().y - this->m_view.getSize().y / 2.f < 0.f)
		{
			this->m_view.setCenter(this->m_view.getCenter().x, 0.f + this->m_view.getSize().y / 2.f);
		}
		else if (this->m_view.getCenter().y + this->m_view.getSize().y / 2.f > this->m_map->getmaxsize().y)
		{
			this->m_view.setCenter(this->m_view.getCenter().x, this->m_map->getmaxsize().y - this->m_view.getSize().y / 2.f);
		}
	}


  this->m_viewgridpos.x = static_cast<int>(this->m_view.getCenter().x / this->m_statedata.gridsize);
  this->m_viewgridpos.y = static_cast<int>(this->m_view.getCenter().y / this->m_statedata.gridsize);


}

inline void gamestate::updateplayerinput(const float &dt) {

  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("MOVE_LEFT")))) {
    m_player->move(dt, -1.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("MOVE_RIGHT")))) {
    m_player->move(dt, 1.f, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("MOVE_UP")))) {
    m_player->move(dt, 0.f, -1.f);
    // m_player->loseexp(10);
  }
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("MOVE_DOWN")))) {
    m_player->move(dt, 0.f, 1.f);
    // m_player->gainexp(10);
  }
}

inline void gamestate::updateplayergui(const float &dt) { m_playergui->update(dt); }

void gamestate::updateinput(const float &dt) {
  // && getkey()
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"]))) {
    //
    if (m_onetime) {
      m_onetime = false;
      if (!m_pause)
        pausestate();
      else
        unpausestate();
    }
    //
  } else {
    m_onetime = true;
  }
}

inline void gamestate::updategui() {
  if (m_pmanu->isbuttenpressed("QUIT")) {
    endstate();
  }
}

inline void gamestate::updatemap(const float &dt) {
  m_map->update();
  m_map->updatecollision(*m_player, dt);
}

void gamestate::update(const float &dt) {
  updatemousepos(&m_view);
  updateinput(dt);

  if (!m_pause) {

    updateview();
    updateplayerinput(dt);
    m_player->update(dt,this->m_mouseposview);
    m_playergui->update(dt);
    updatemap(dt);

  } else {
    m_pmanu->update(m_mouseposwindow);
    updategui();
  }
}

void gamestate::render(sf::RenderTarget *target) {

  if (!target)
    target = m_window;

  m_rendertexture.clear();

  m_rendertexture.setView(m_view);

  m_map->render(m_rendertexture,
                m_viewgridpos,
                m_player->getentitycenter(),
                &m_core_sheder,true);

  m_player->render(m_rendertexture,
                &m_core_sheder,true);

  m_map->deferredrender(m_rendertexture,m_player->getentitycenter(),&m_core_sheder);

  m_rendertexture.setView(m_rendertexture.getDefaultView());

  m_playergui->render(m_rendertexture);

  if (m_pause) {
    m_pmanu->render(m_rendertexture);
  }

  m_rendertexture.display();
  m_rendersprite.setTexture(m_rendertexture.getTexture());
  target->draw(m_rendersprite);
}