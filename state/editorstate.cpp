#pragma once

#include "editorstate.h"

inline void editorstate::initvar() {
  m_onetime = true;
  m_addtilelock = false;
  m_collision = false;
  m_type = tiletype::DEFALUT;
  m_viewspeed = 100.f;
  m_layer = 0;
  m_lastselectorgrid.x = -1;
  m_lastselectorgrid.y = -1;
}

inline void editorstate::initview() {
  m_view.setSize(sf::Vector2f(m_statedata.gfsettings->resolution.width,
                              m_statedata.gfsettings->resolution.height));
  m_view.setCenter(sf::Vector2f(m_view.getSize() / 2.f));
}

inline void editorstate::initbackground() {}

inline void editorstate::initfont() {
  if (!m_font.loadFromFile("./resource/Font/main_manu_font.otf")) {
    throw("Error:- STATE::EDITORSTATE::intfont() Load font file falled.\n");
  }
}

inline void editorstate::inittext() {
  m_cursortext.setFillColor(sf::Color::White);
  m_cursortext.setFont(m_font);
  m_cursortext.setCharacterSize(12);
}

void editorstate::initkeybinds() {

  std::ifstream ifs("./resource/editorkey.ini");

  if (ifs.is_open()) {

    std::string key = "";
    std::string key2 = "";

    while (ifs >> key >> key2) {
      m_keybinds[key] = m_supportedkeys->at(key2);
    }
  }
  ifs.close();
}

inline void editorstate::initgui() {

  m_siderbar.setSize(sf::Vector2f(
      100.f, static_cast<float>(m_statedata.gfsettings->resolution.height)));
  m_siderbar.setFillColor(sf::Color(50, 50, 50, 100));
  m_siderbar.setOutlineColor(sf::Color(200, 200, 200, 150));
  m_siderbar.setOutlineThickness(1.f);

  m_texturerect = sf::IntRect(0, 0, static_cast<int>(m_statedata.gridsize),
                              static_cast<int>(m_statedata.gridsize));

  m_textureselector = new gui::textureselector(
      m_window->getSize().x / 2.f - 100.f, m_window->getSize().y - 175.f,
      m_statedata.gridsize * 2.f,
      m_statedata.gridsize + m_statedata.gridsize / 2.f, m_map->gettilesheet(),
      m_font, "TS", m_statedata.gridsize);
}

inline void editorstate::initpause() {
  const sf::VideoMode &vm = this->m_statedata.gfsettings->resolution;
  m_pmanu = new pausemanu(vm, m_font);

  float w = gui::p2pX(13.02f, vm);
  float h = gui::p2pY(5.55f, vm);
  unsigned charsize = gui::calccharsize(vm);

  m_pmanu->addbutten("QUIT", gui::p2pY(44.44f, vm), w, h, charsize, "Quit");
  m_pmanu->addbutten("SAVE", gui::p2pY(33.33f, vm), w, h, charsize, "Save");
  m_pmanu->addbutten("LOAD", gui::p2pY(22.22f, vm), w, h, charsize, "Load");
}

inline void editorstate::initselector() {}

inline void editorstate::inittilemap() {
  m_map = new tilemap(m_statedata.gridsize, 100, 100,
                      "./resource/tile/tilesheet3.png");
  // m_map->loadmapfile("map.slmp");
}

editorstate::editorstate(statedata &data)
    : state(data), m_selectorhelper(true), m_keypresshelper(true) {

  initvar();

  initview();

  initbackground();

  initfont();

  inittext();

  initkeybinds();

  initpause();

  inittilemap();

  initselector();

  initgui();
}

editorstate::~editorstate() {
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    delete i.second;
  }

  delete m_pmanu;

  delete m_map;

  delete m_textureselector;
}

void editorstate::updateinput(const float &dt) {
  if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds.at("CLOSE")))) {
    m_onetime = true;
    goto skippausestate;
  }

  if (m_onetime) {
    m_onetime = false;
    if (m_pause)
      unpausestate();
    else
      pausestate();
  }
skippausestate:
  if (m_keypress.timefram(100)) {
    m_keypresshelper = true;
  }

  if (!m_keypresshelper)
    return;

  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("TOGGLE_COLLISION")))) {
    m_collision = !m_collision;
  } else if (sf::Keyboard::isKeyPressed(
                 sf::Keyboard::Key(m_keybinds.at("INCREASE_TYPE")))) {
    // change it to max limit
    m_type++;
  } else if (sf::Keyboard::isKeyPressed(
                 sf::Keyboard::Key(m_keybinds.at("DECREASE_TYPE")))) {
    if (m_type)
      m_type--;
  }
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("TOGGLE_TILE_LOCK")))) {
    this->m_addtilelock = !this->m_addtilelock;
  }
  m_keypresshelper = false;
}

inline void editorstate::updateview(const float &dt) {
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("MOVE_CAMERA_LEFT")))) {
    m_view.move(-(m_viewspeed * dt), 0.f);
  }
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("MOVE_CAMERA_RIGHT")))) {
    m_view.move(m_viewspeed * dt, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("MOVE_CAMERA_UP")))) {
    m_view.move(0.f, -m_viewspeed * dt);
  }
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Key(m_keybinds.at("MOVE_CAMERA_DOWN")))) {
    m_view.move(0.f, m_viewspeed * dt);
  }
}
void editorstate::updateeditinput(const float &dt) {
  // if (m_lastselectorgrid.x != m_mouseposgrid.x ||
  //     m_lastselectorgrid.y != m_mouseposgrid.y) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        !m_siderbar.getGlobalBounds().contains(m_mouseposview) &&
         (!m_addtilelock || m_map->gettileisaddon(m_mouseposgrid.x, m_mouseposgrid.y, 0))) {

        m_map->addtile(m_mouseposgrid.x, m_mouseposgrid.y, 0, m_texturerect,
                       m_collision, m_type);
        // m_lastselectorgrid = m_mouseposgrid;
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
               !m_siderbar.getGlobalBounds().contains(m_mouseposview)) {
      m_map->removetile(m_mouseposgrid.x, m_mouseposgrid.y, 0);
      // m_lastselectorgrid = m_mouseposgrid;
    }
  // }

  // if(){if(){}if(){}}
  // 95 milliseconds after
  if (m_timelimitforselector.timefram(95)) {
    m_selectorhelper = true;
  }

  if (!m_selectorhelper)
    return;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    m_textureselector->updateactiveindex(1);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    m_textureselector->updateactiveindex(-1);
  }
  m_selectorhelper = false;
}

inline void editorstate::updatepausemanuinput() {
  if (m_pmanu->isbuttenpressed("QUIT")) {
    endstate();
  }
  if (m_pmanu->isbuttenpressed("SAVE")) {
    m_map->savemapfile("map.slmp");
  }
  if (m_pmanu->isbuttenpressed("LOAD")) {
    m_map->loadmapfile("map.slmp");
  }
}

void editorstate::updategui() {
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    i.second->update(m_mouseposwindow);
  }
}

inline void editorstate::updateselector() {

  if (m_textureselector->getupdated()) {
    m_texturerect = m_textureselector->getactiverect();
  }

  std::stringstream ss;
  ss << m_mouseposview.x << "  " << m_mouseposview.y << '\n'
     << m_texturerect.left /64<< "  " << m_texturerect.top /64<< '\n'
     << m_mouseposgrid.x << "  " << m_mouseposgrid.y << '\n'
     << "Collison : " << m_collision << '\n'
     << "Type : " << m_type << '\n'
     << "Tile Layer:"
     << m_map->getlayersize(m_mouseposgrid.x, m_mouseposgrid.y, m_layer) << '\n'
     << "Tile lock:" << m_addtilelock;

  m_cursortext.setString(ss.str());
  m_cursortext.setPosition(m_mouseposview.x, m_mouseposview.y - 100.f);
}

void editorstate::update(const float &dt) {
  updatemousepos(&m_view);

  updatekeytime(dt);

  updateinput(dt);

  if (!m_pause) {
    m_textureselector->update(m_mouseposwindow);
    updateview(dt);
    updateeditinput(dt);
    updateselector();
    updategui();
    m_map->update();

  } else {
    m_pmanu->update(m_mouseposwindow);
    updatepausemanuinput();
  }
}

void editorstate::rendergui(sf::RenderTarget &target) {
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    i.second->render(target);
  }
}

inline void editorstate::renderselector(sf::RenderTarget &target) {

  target.setView(m_window->getDefaultView());
  m_textureselector->render(target);
  target.draw(m_siderbar);

  target.setView(m_view);
  target.draw(m_cursortext);
}

void editorstate::render(sf::RenderTarget *target) {
  if (!target)
    target = m_window;

  target->setView(m_view);

  m_map->render(*target, m_mouseposgrid, sf::Vector2f(), nullptr, true);
  m_map->deferredrender(*target);

  target->setView(m_window->getDefaultView());

  rendergui(*target);
  renderselector(*target);

  if (m_pause) {
    target->setView(m_window->getDefaultView());
    m_pmanu->render(*target);
  }
}