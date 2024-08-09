#include "settingstate.h"
void settingstate::initvar() {
  m_modes = sf::VideoMode::getFullscreenModes();
  m_activemode = -1;
  // for (sf::VideoMode &i : m_modes) {
  //     m_modes_str.push_back(std::to_string(i.width) + 'x' +
  //     std::to_string(i.height));
  // }

  for (int i = 0; i < m_modes.size(); i++) {
    if (m_modes.at(i).width == m_window->getSize().x &&
        m_modes.at(i).height == m_window->getSize().y)
      m_activemode = i;
    m_modes_str.push_back(std::to_string(m_modes.at(i).width) + 'x' +
                          std::to_string(m_modes.at(i).height));
  }

  m_dropdownhelper = true;
}

inline void settingstate::initbackground() {
  m_background.setSize(static_cast<sf::Vector2f>(m_window->getSize()));

  if (!m_backgroundtexture.loadFromFile("./resource/background/setting.png"))
    throw std::runtime_error(
        "Error: STATE::MAINSTATE::initbackground failed to load background.");

  m_background.setTexture(&m_backgroundtexture);
}

inline void settingstate::initfont() {
  if (!m_font.loadFromFile("./resource/Font/main_manu_font.otf")) {
    throw std::runtime_error(
        "Error: STATE::MAINMANUSTATE::initfont() failed to load font file.");
  }
}

void settingstate::initkeybinds() {
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

void settingstate::initgui() {
  const sf::VideoMode &vm = this->m_statedata.gfsettings->resolution;
  unsigned charsize = gui::calccharsize(vm);
  float width = gui::p2pX(13.02f, vm);
  float height = gui::p2pY(5.55f, vm);

  m_butten["BACK"] = new gui::butten(
      gui::p2pX(17.18f, vm), gui::p2pY(60.f, vm), width, height, m_font, "Back",
      charsize, sf::Color(250, 250, 250, 250), sf::Color::Red,
      sf::Color(20, 20, 20, 50), sf::Color(100, 100, 100, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

  m_butten["APPLY"] = new gui::butten(
      gui::p2pX(3.64f, vm), gui::p2pY(60.f, vm), width, height, m_font, "Apply",
      charsize, sf::Color(250, 250, 250, 250), sf::Color::Green,
      sf::Color(20, 20, 20, 50), sf::Color(100, 100, 100, 0),
      sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

  m_dropdownlist["RESOLUTION"] = new gui::dropdownlist(
      gui::p2pX(15.625f, vm), gui::p2pY(11.11f, vm), gui::p2pX(10.41f, vm),
      gui::p2pY(4.44f, vm), m_font, m_modes_str.data(),
      gui::calccharsize(vm, 110), m_modes_str.size(),
      std::to_string(vm.width) + 'x' + std::to_string(vm.height), m_activemode);

  m_optionstext.setFont(m_font);
  m_optionstext.setPosition(
      sf::Vector2f(gui::p2pX(5.2f, vm), gui::p2pY(11.11f, vm)));
  m_optionstext.setCharacterSize(gui::calccharsize(vm, 75));
  m_optionstext.setFillColor(sf::Color(255, 255, 255, 200));
  m_optionstext.setString("Resolution \nFullscreen \nVsync \nAntialiasing \n");
}

settingstate::settingstate(statedata &data)
    : state(data), m_gfsetting(*data.gfsettings) {
  initvar();
  initbackground();
  initfont();
  initkeybinds();
  initgui();
}

settingstate::~settingstate() {
  this->cleanupgui();
}

void settingstate::cleanupgui (){
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    delete i.second;
  }
  for (std::pair<const std::string, gui::dropdownlist *> &i : m_dropdownlist) {
    delete i.second;
  }
}

void settingstate::resetgui() {
  // reset main manu's gui 
  //{
    state* selfstate = m_states->top();
    m_states->pop();

    if(m_states->top()->getstateType() == State_Type::MAIN_MANU)m_states->top()->resetgui();

    m_states->push(selfstate);
  //}
  
  this->cleanupgui();

  m_butten.clear();
  m_dropdownlist.clear();
  m_background.setSize(static_cast<sf::Vector2f>(m_window->getSize()));
  
  initgui();
}

inline void settingstate::updateinput(const float &dt) {
  // Update input (e.g., keyboard input)
}

void settingstate::updategui() {
  if (!m_dropdownlist["RESOLUTION"]->getshowlist()) {
    for (std::pair<const std::string, gui::butten *> &i : m_butten) {
      i.second->update(m_mouseposwindow);
    }
  }

  for (std::pair<const std::string, gui::dropdownlist *> &i : m_dropdownlist) {
    i.second->update(m_mouseposwindow);
  }

  if (m_butten["BACK"]->ispressed()) {
    endstate();
  }

  if (!m_butten["APPLY"]->ispressed()) {
    return;
  }
  if (m_dropdownlist.at("RESOLUTION")->getactiveid() == m_activemode) {
    return;
  }
  
  m_activemode = m_dropdownlist.at("RESOLUTION")->getactiveid();
  m_gfsetting.resolution = m_modes.at(m_activemode);
  m_window->create(m_gfsetting.resolution, m_gfsetting.title,
                   sf::Style::Default);
  resetgui();
}

inline void settingstate::update(const float &dt) {
  updatemousepos();
  updateinput(dt);
  updategui();
}

void settingstate::rendergui(sf::RenderTarget &target) {
  for (std::pair<const std::string, gui::butten *> &i : m_butten) {
    i.second->render(target);
  }
  for (std::pair<const std::string, gui::dropdownlist *> &i : m_dropdownlist) {
    i.second->render(target);
  }
}

inline void settingstate::render(sf::RenderTarget *target) {
  if (!target) {
    target = m_window;
  }

  target->draw(m_background);
  rendergui(*target);
  target->draw(m_optionstext);
}
