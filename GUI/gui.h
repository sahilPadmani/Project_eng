#pragma once

#include "../preheader.hpp"

enum BUTTEN_TYPE { IDEL = 0, HOVED, PRESSED };

namespace gui {

static const inline bool isMouseClicked(sf::Mouse::Button button);
static constexpr inline float p2pX(const float &perc, const sf::VideoMode &vm);
static constexpr inline float p2pY(const float &perc, const sf::VideoMode &vm);
static constexpr inline unsigned calccharsize(const sf::VideoMode &vm,
                                              const unsigned &modifier = 65);

class butten {
  short unsigned m_buttentype;
  int m_id;

  sf::Color m_buttencurentcolor;
  sf::Color m_textcurentcolor;
  sf::Color m_outlinecurentcolor;

  sf::Color m_textidel;
  sf::Color m_texthoved;
  sf::Color m_textpressed;

  sf::Color m_idel;
  sf::Color m_hoved;
  sf::Color m_pressed;

  sf::Color m_outlineidel;
  sf::Color m_outlinehoved;
  sf::Color m_outlinepressed;

  sf::RectangleShape m_shap;
  sf::Font *m_font;
  sf::Text m_text;

  // void intcolor();

public:
  butten(const float &x, const float &y, const float &widht, const float &hight,
         sf::Font &font, const std::string &text, const unsigned &charsize,
         const sf::Color &text_idel, const sf::Color &text_hoved,
         const sf::Color &text_pressed, const sf::Color &idel,
         const sf::Color &hoved, const sf::Color &pressed,
         const sf::Color &outlineidel = sf::Color::Transparent,
         const sf::Color &outlinehoved = sf::Color::Transparent,
         const sf::Color &outlinepressed = sf::Color::Transparent,
         const int &id = -1);
  virtual ~butten();

  inline const bool ispressed() const;

  inline const int &getid() const;
  inline void setid(const int &id);

  inline const std::string gettext() const;
  inline void settext(const std::string &text);

  void update(const sf::Vector2i &mouse);
  inline void render(sf::RenderTarget &target);
};

class dropdownlist {

private:
  sf::Font &m_font;
  butten *m_activeelement;
  std::vector<butten *> m_list;
  bool m_showlist;
  bool m_onetime;

public:
  dropdownlist(const float &x, const float &y, const float &w, const float &h,
               sf::Font &font, const std::string list[],
               const unsigned &charsize, const unsigned &no_of_str,
               const std::string &defult_str, const int &defult_index = -1);
  virtual ~dropdownlist();

  void activeelementclick();
  inline const int &getactiveid() const;
  inline const bool getshowlist() const;

  void update(const sf::Vector2i &mouse);
  void render(sf::RenderTarget &target);
};

class textureselector {
  int m_activeindex;
  bool m_updated;
  bool m_hidden;
  butten *m_hidebutten;
  clocktimer m_hidetimer;
  bool m_timerhelp;

  sf::RectangleShape m_backgroundshap;
  sf::RectangleShape m_active;
  std::vector<sf::RectangleShape> m_list;

  void initvec(const sf::Texture &texture, const float &gridsize);

public:
  textureselector(const float &x, const float &y, const float &w,
                  const float &h, const sf::Texture *texture, sf::Font &font,
                  const std::string_view text, const float &gridsize);
  virtual ~textureselector();

  void updateactiveindex(const int &i);
  inline const bool getupdated();
  inline const sf::IntRect &getactiverect();

  void update(const sf::Vector2i &mouseview);
  void render(sf::RenderTarget &target);
};

class progressbar {
  sf::Text m_text;
  sf::Vector2f m_barmaxsize;
  sf::Vector2f m_pos;
  sf::RectangleShape m_bargreen;
  sf::RectangleShape m_barback;
public:
  progressbar(const float &x, const float &y, const float &w,
                         const float &h, const sf::VideoMode &vm,
                        const sf::Font *font = nullptr);
  virtual ~progressbar();

  void update(const float& percent , const std::string& text);
  void render(sf::RenderTarget& target);
};
} // namespace gui