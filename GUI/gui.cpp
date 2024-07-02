#pragma once

#include "gui.h"

// void butten::intcolor (){
//     m_idel =
// }
namespace gui {

/**
 * @param perc The `perc` parameter represents a percentage value that is used
 * to calculate a position along the x-axis based on the width of the default
 * video mode.
 *
 * @return The function `p2pX` is returning the result of the calculation, which
 * is the floor value of the product of the default video mode width and the
 * percentage provided as input.
 */
static constexpr inline float p2pX(const float &perc, const sf::VideoMode &vm) {
  return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

static constexpr inline float p2pY(const float &perc, const sf::VideoMode &vm) {
  return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

static constexpr inline unsigned calccharsize(const sf::VideoMode &vm,
                                              const unsigned &modifier) {
  return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

static const inline bool isMouseClicked(sf::Mouse::Button button) {
  static bool wasButtonPressed = false;
  bool isButtonPressed = sf::Mouse::isButtonPressed(button);

  if (!wasButtonPressed && isButtonPressed) {
    wasButtonPressed = true;
    return true;
  }

  wasButtonPressed = isButtonPressed;
  return false;
}

//======================================butten=================================================
butten::butten(const float &x, const float &y, const float &widht,
               const float &hight, sf::Font &font, const std::string &text,
               const unsigned &charsize, const sf::Color &text_idel,
               const sf::Color &text_hoved, const sf::Color &text_pressed,
               const sf::Color &idel, const sf::Color &hoved,
               const sf::Color &pressed, const sf::Color &outlineidel,
               const sf::Color &outlinehoved, const sf::Color &outlinepressed,
               const int &id) {

  m_buttentype = BUTTEN_TYPE::IDEL;
  m_id = id;

  m_shap.setPosition(sf::Vector2f(x, y));
  m_shap.setSize(sf::Vector2f(widht, hight));
  m_shap.setOutlineThickness(1.f);

  m_font = &font;
  m_text.setFont(*m_font);
  m_text.setString(text);
  m_text.setCharacterSize(charsize);
  m_text.setFillColor(text_idel);
  m_text.setPosition(
      m_shap.getPosition().x +
          (m_shap.getGlobalBounds().width - m_text.getGlobalBounds().width) /
              2.f,
      m_shap.getPosition().y +
          (m_shap.getGlobalBounds().height - m_text.getGlobalBounds().height) /
              2.f);

  m_textidel = text_idel;
  m_texthoved = text_hoved;
  m_textpressed = text_pressed;

  m_idel = idel;
  m_hoved = hoved;
  m_pressed = pressed;

  m_outlineidel = outlineidel;
  m_outlinehoved = outlinehoved;
  m_outlinepressed = outlinepressed;
}

butten::~butten() {}

inline const bool butten::ispressed() const {
  return m_buttentype == BUTTEN_TYPE::PRESSED;
}

inline const int &gui::butten::getid() const { return this->m_id; }
inline void gui::butten::setid(const int &id) { this->m_id = id; }

inline const std::string butten::gettext() const {
  return this->m_text.getString();
}

inline void butten::settext(const std::string &text) { m_text.setString(text); }

void butten::update(const sf::Vector2i &mouse) {

  m_buttentype = BUTTEN_TYPE::IDEL;

  if (m_shap.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {

    m_buttentype = BUTTEN_TYPE::HOVED;

    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //   m_buttentype = BUTTEN_TYPE::PRESSED;
    // }
    if (gui::isMouseClicked(sf::Mouse::Left)) {
      m_buttentype = BUTTEN_TYPE::PRESSED;
    }
  }

  switch (m_buttentype) {

  case BUTTEN_TYPE::HOVED:
    m_buttencurentcolor = m_hoved;
    m_textcurentcolor = m_texthoved;
    m_outlinecurentcolor = m_outlinehoved;
    break;
  case BUTTEN_TYPE::PRESSED:
    m_buttencurentcolor = m_pressed;
    m_textcurentcolor = m_textpressed;
    m_outlinecurentcolor = m_outlinepressed;
    break;
  default:
    m_buttencurentcolor = m_idel;
    m_textcurentcolor = m_textidel;
    m_outlinecurentcolor = m_outlineidel;
    break;
  }

  m_shap.setFillColor(m_buttencurentcolor);
  m_shap.setOutlineColor(m_outlinecurentcolor);
  m_text.setFillColor(m_textcurentcolor);
}

inline void butten::render(sf::RenderTarget &target) {
  target.draw(m_shap);
  target.draw(m_text);
}

//======================================drop down list
//=====================================================//

dropdownlist::dropdownlist(const float &x, const float &y, const float &w,
                           const float &h, sf::Font &font,
                           const std::string list[], const unsigned &charsize,
                           const unsigned &no_of_str,
                           const std::string &defult_str,
                           const int &defult_index)
    : m_font(font), m_showlist(false) {
  m_activeelement =
      new butten(x, y, w, h, m_font, defult_str, charsize,
                 sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200),
                 sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),
                 sf::Color(150, 150, 150, 200), sf::Color(150, 150, 150, 200),
                 sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255),
                 sf::Color(255, 255, 255, 255), defult_index);

  for (int i = 0; i < no_of_str; i++) {
    m_list.push_back(
        new butten(x, y + ((1 + i) * h), w, h, m_font, list[i], charsize,
                   sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255),
                   sf::Color(255, 255, 255, 255), sf::Color(70, 70, 70, 200),
                   sf::Color(150, 150, 150, 200), sf::Color(150, 150, 150, 200),
                   sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0),
                   sf::Color(255, 255, 255, 0), i));
  }
}

dropdownlist::~dropdownlist() {
  delete m_activeelement;
  for (gui::butten *i : m_list) {
    delete i;
  }
}

inline const int &dropdownlist::getactiveid() const {
  return this->m_activeelement->getid();
}

inline const bool dropdownlist::getshowlist() const { return this->m_showlist; }

void dropdownlist::activeelementclick() {
  if (m_activeelement->ispressed()) {
    if (m_onetime) {
      m_onetime = false;
      m_showlist = !m_showlist;
    }
  } else {
    m_onetime = true;
  }
}

void dropdownlist::update(const sf::Vector2i &mouse) {
  m_activeelement->update(mouse);
  activeelementclick();

  if (m_showlist) {
    for (butten *&i : m_list) {
      i->update(mouse);
      if (i->ispressed()) {
        m_showlist = false;
        m_activeelement->settext(i->gettext());
        m_activeelement->setid(i->getid());
      }
    }
  }
}

void dropdownlist::render(sf::RenderTarget &target) {
  m_activeelement->render(target);
  if (m_showlist) {
    for (butten *&i : m_list) {
      i->render(target);
    }
  }
}

//=================================== textureselector
//=======================================

void textureselector::initvec(const sf::Texture &texture,
                              const float &gridsize) {
  int x = (texture.getSize().x * texture.getSize().y) / (gridsize * gridsize);

  sf::RectangleShape tempshap;
  sf::IntRect temprect(0, 0, static_cast<int>(gridsize),
                       static_cast<int>(gridsize));

  for (int i = 0; i < x; ++i) {
    tempshap.setSize(sf::Vector2f(gridsize, gridsize));
    tempshap.setTexture(&texture);
    tempshap.setTextureRect(temprect);
    tempshap.setPosition(
        static_cast<float>(temprect.left) +
            (m_backgroundshap.getPosition().x + tempshap.getSize().x) / 2.f,
        static_cast<float>(temprect.top) +
            (m_backgroundshap.getPosition().y + tempshap.getSize().y) / 2.f);
    m_list.push_back(tempshap);

    if (temprect.left + static_cast<int>(gridsize) < texture.getSize().x) {
      temprect.left += static_cast<int>(gridsize);
    } else {
      temprect.left = 0;
      temprect.top += static_cast<int>(gridsize);
    }
  }
}

textureselector::textureselector(const float &x, const float &y, const float &w,
                                 const float &h, const sf::Texture *texture,
                                 sf::Font &font, const std::string_view text,
                                 const float &gridsize)
    : m_activeindex(0), m_updated(false), m_hidden(true) {
  m_backgroundshap.setSize(sf::Vector2f(w, h));
  m_backgroundshap.setPosition(x, y);
  m_backgroundshap.setFillColor(sf::Color(50, 50, 50, 20));
  m_backgroundshap.setOutlineThickness(1.f);
  m_backgroundshap.setOutlineColor(sf::Color::White);

  initvec(*texture, gridsize);

  m_active.setSize(sf::Vector2f(gridsize, gridsize));
  m_active.setPosition(x + (w - gridsize) / 2.f, y + (h - gridsize) / 2.f);
  m_active.setTexture(texture);
  m_active.setTextureRect(m_list.at(m_activeindex).getTextureRect());

  m_hidebutten =
      new butten(20.f, 25.f, 50.f, 50.f, font, std::string(text), 30,
                 sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250),
                 sf::Color(255, 255, 255, 50), sf::Color(70, 70, 70, 200),
                 sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));
}

textureselector::~textureselector() { delete m_hidebutten; }

void textureselector::updateactiveindex(const int &i) {
  if (m_activeindex + i < 0) {
    m_activeindex = 0;
  } else if (m_activeindex + i >= static_cast<int>(m_list.size())) {
    m_activeindex = static_cast<int>(m_list.size()) - 1;
  } else {
    m_activeindex += i;
  }
  m_updated = true;
}

inline const sf::IntRect &textureselector::getactiverect() {
  m_active.setTextureRect(m_list.at(m_activeindex).getTextureRect());
  return m_active.getTextureRect();
}

inline const bool textureselector::getupdated() {
  bool was_updated = m_updated;
  m_updated = false; // Reset the flag after checking
  return was_updated;
}

void textureselector::update(const sf::Vector2i &mouseview) {
  if (m_hidetimer.timefram(900)) {
    m_timerhelp = true;
  }
  if (m_timerhelp) {
    m_hidebutten->update(mouseview);

    if (m_hidebutten->ispressed()) {
      m_timerhelp = false;
      m_hidden = !m_hidden;
    }
  }

  if (m_hidden) {
    return;
  }

  m_updated = false; // Reset the update flag
  // for (unsigned count = 0; count < m_list.size(); ++count) {
  //   if (!m_list.at(count).getGlobalBounds().contains(mouseview)) {
  //     m_list.at(count).setOutlineThickness(0.f);
  //     continue;
  //   }
  //   m_list.at(count).setOutlineThickness(1.f);
  //   m_list.at(count).setOutlineColor(sf::Color::Red);
  //   if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
  //     m_activeindex = count;
  //     m_updated = true;
  //   }
  // }
}

void textureselector::render(sf::RenderTarget &target) {
  m_hidebutten->render(target);
  if (m_hidden) {
    return;
  }
  target.draw(m_backgroundshap);
  target.draw(m_active);
  // for (const auto &i : m_list) {
  //   target.draw(i);
  // }
}
//================================ progress
// bar======================================

progressbar::progressbar(const float &x, const float &y, const float &w,
                        const float &h, const sf::VideoMode &vm,
                        const sf::Font *font) {

  m_barmaxsize = sf::Vector2f(gui::p2pX(w, vm), gui::p2pY(h, vm));
  m_pos = sf::Vector2f(gui::p2pX(x, vm), gui::p2pY(y, vm));

  m_barback.setSize(m_barmaxsize);
  m_barback.setFillColor(sf::Color(50, 50, 50, 200));
  m_barback.setPosition(m_pos);

  // both are same only color are diffrent
  m_bargreen = m_barback;
  m_bargreen.setFillColor(sf::Color::Green);
  if (font) {
    m_text.setFont(*font);
    m_text.setCharacterSize(gui::calccharsize(vm, 100));
    m_text.setPosition(m_pos.x + gui::p2pX(0.52f, vm),
                       m_pos.y + gui::p2pY(0.26f, vm));
  }
}

progressbar::~progressbar(){}

void progressbar::update(const float& percent , const std::string& text){
  m_bargreen.setSize(
      sf::Vector2f(std::floor(m_barmaxsize.x * percent),
                   m_barmaxsize.y));

  m_text.setString(text);
}

void progressbar::render(sf::RenderTarget& target){
  target.draw(m_barback);
  target.draw(m_bargreen);
  target.draw(m_text);
}

} // namespace gui