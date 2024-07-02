#pragma once

#include "tilemap.h"

void tilemap::clearmap() {
  if (m_map.empty())
    return;
  for (int i = 0; i < m_maxgridsize.x; ++i) {
    for (int j = 0; j < m_maxgridsize.y; ++j) {
      for (int k = 0; k < m_layers; ++k) {
        for (int l = 0; l < m_map[i][j][k].size(); ++l) {
          delete m_map[i][j][k][l];
          m_map[i][j][k][l] = nullptr;
        }
        m_map[i][j][k].clear();
      }
      m_map[i][j].clear();
    }
    m_map[i].clear();
  }
  m_map.clear();
}

inline void tilemap::resizemap() {
  m_map.resize(m_maxgridsize.x,
               std::vector<std::vector<std::vector<tile *>>>(
                   m_maxgridsize.y, std::vector<std::vector<tile *>>(
                                        m_layers, std::vector<tile *>())));
}

inline void tilemap::inittexture() {
  if (!m_tilesheet.loadFromFile(m_texturefilepath)) {
    throw("ERROR::TILEMAP:: imag load falled.\n");
  }
}

inline void tilemap::initcollisionbox() {
  m_collisionbox.setSize(sf::Vector2f(m_gridsizef, m_gridsizef));
  m_collisionbox.setFillColor(sf::Color(250, 0, 0, 50));
}
tilemap::tilemap(const float &griedsize, const int &h, const int &w,
                 const std::string_view &texturefilepath)
    : m_fromx(0), m_tox(0), m_fromy(0), m_toy(0), m_tolayer(0) {
  m_gridsizef = griedsize;
  m_gridsizei = static_cast<int>(m_gridsizef);
  m_maxgridsize.x = w;
  m_maxgridsize.y = h;
  m_maxmapsize.x = static_cast<float>(w) * m_gridsizef;
  m_maxmapsize.y = static_cast<float>(h) * m_gridsizef;
  m_layers = 1;
  m_texturefilepath = std::string(texturefilepath);

  resizemap();
  // change it png.
  inittexture();

  initcollisionbox();
}

tilemap::tilemap(const std::string &file_name)
    : m_fromx(0), m_tox(0), m_fromy(0), m_toy(0), m_tolayer(0) {
  loadmapfile(file_name);
  initcollisionbox();
}

tilemap::~tilemap() { clearmap(); }

inline const bool tilemap::gettileisaddon(const int &x, const int &y,
                                   const int &z) const {
  if (x < m_maxgridsize.x && x >= 0 && y < m_maxgridsize.y && y >= 0 &&
      z < m_layers && z >= 0) {
    return m_map.at(x).at(y).at(z).empty();
  }
  return false;
}

inline const sf::Texture *tilemap::gettilesheet() const { return &this->m_tilesheet; }
inline const int tilemap::getlayersize(const int &grid_x, const int &grid_y,
                                const int &layer) const {
  if (!(grid_x < m_maxgridsize.x && grid_x >= 0 && grid_x < m_maxgridsize.y &&
        grid_x >= 0 && layer < m_layers && layer >= 0))
    return -1;
  return m_map[grid_x][grid_y][layer].size();
}

inline const sf::Vector2f &tilemap::getmaxsize() const { return this->m_maxmapsize; }
inline const sf::Vector2i &tilemap::getmaxgrid() const { return this->m_maxgridsize; }
void tilemap::update() {}

inline void tilemap::addtile(const int &x, const int &y, const int &z,
                      const sf::IntRect &texture_rect, const bool &collision,
                      const short &type) {
  if (!(x < m_maxgridsize.x && x >= 0 && y < m_maxgridsize.y && y >= 0 &&
        z < m_layers && z >= 0))
    return;
  m_map[x][y][z].push_back(
      new tile(x, y, m_gridsizef, m_tilesheet, texture_rect, collision, type));
}

inline void tilemap::removetile(const int &x, const int &y, const int &z) {
  if (!(x < m_maxgridsize.x && x >= 0 && y < m_maxgridsize.y && y >= 0 &&
        z < m_layers && z >= 0))
    return;

  if (!m_map[x][y][z].empty()) {
    delete m_map[x][y][z][m_map[x][y][z].size() - 1];
    m_map[x][y][z].pop_back();
  }
}

void tilemap::renderfullmap(sf::RenderTarget &target) {
  for (int i = 0; i < m_maxgridsize.x; ++i) {
    for (int j = 0; j < m_maxgridsize.y; ++j) {
      for (int k = 0; k < m_layers; ++k) {
        for (int l = 0; l < m_map[i][j][k].size(); ++l) {
          m_map[i][j][k][l]->render(target);
          if (m_map[i][j][k][l]->getcollison()) {
            m_collisionbox.setPosition(m_map[i][j][k][l]->gettilepos());
            target.draw(m_collisionbox);
          }
        }
      }
    }
  }
}

inline void tilemap::activegrid(const sf::Vector2i &gridpos) {
  m_tolayer = 0;

  // gridpos = entity.getgridpos(m_gridsizei);

  m_fromx = gridpos.x - 15;
  if (m_fromx < 0)
    m_fromx = 0;
  else if (m_fromx > m_maxgridsize.x)
    m_fromx = m_maxgridsize.x;

  m_tox = gridpos.x + 16;
  if (m_tox < 0)
    m_tox = 0;
  else if (m_tox > m_maxgridsize.x)
    m_tox = m_maxgridsize.x;

  m_fromy = gridpos.y - 8;
  if (m_fromy < 0)
    m_fromy = 0;
  else if (m_fromy > m_maxgridsize.y)
    m_fromy = m_maxgridsize.y;

  m_toy = gridpos.y + 9;
  if (m_toy < 0)
    m_toy = 0;
  else if (m_toy > m_maxgridsize.y)
    m_toy = m_maxgridsize.y;
}

void tilemap::deferredrender(sf::RenderTarget &target,
                             const sf::Vector2f &playerpos,
                             sf::Shader *shader) {
  while (!m_deferredrenderstack.empty()) {
    m_deferredrenderstack.top()->render(target, playerpos, shader);
    m_deferredrenderstack.pop();
  }
}
void tilemap::render(sf::RenderTarget &target,
                     const sf::Vector2i &entitygridpos,
                     const sf::Vector2f playerpos, sf::Shader *shader,
                     const bool &show_collison) {

  activegrid(entitygridpos);

  for (int i = m_fromx; i < m_tox; ++i) {
    for (int j = m_fromy; j < m_toy; ++j) {
      if (m_map[i][j][m_tolayer].empty())
        continue;
      for (int k = 0; k < m_map[i][j][m_tolayer].size(); ++k) {
        if (m_map[i][j][m_tolayer][k]->gettype() == tiletype::POSTDRAW) {
          m_deferredrenderstack.push(m_map[i][j][m_tolayer][k]);
        } else {
          m_map[i][j][m_tolayer][k]->render(target, playerpos, shader);
        }
        if (!show_collison)
          continue;
        if (m_map[i][j][m_tolayer][k]->getcollison()) {
          m_collisionbox.setPosition(m_map[i][j][m_tolayer][k]->gettilepos());
          target.draw(m_collisionbox);
        }
      }
    }
  }
}

void tilemap::savemapfile(const std::string_view filename) {
  std::ofstream savefile;
  savefile.open(std::string(filename));

  if (savefile.is_open()) {

    savefile << m_maxgridsize.x << ' ' << m_maxgridsize.y << '\n'
             << m_gridsizei << '\n'
             << m_layers << '\n'
             << m_texturefilepath << '\n';

    for (int i = 0; i < m_maxgridsize.x; ++i) {
      for (int j = 0; j < m_maxgridsize.y; ++j) {
        for (int k = 0; k < m_layers; ++k) {
          if (m_map[i][j][k].empty())
            continue;
          for (int l = 0; l < m_map[i][j][k].size(); ++l) {
            savefile << i << ' ' << j << ' ' << k << ' '
                     << m_map[i][j][k][l]->getstring() << ' ';
          }
        }
      }
    }

  } else {
    std::cout << "Error::TILEMAP::SAVEMAPFILE failed to save map in file.\n";
  }

  savefile.close();
}
void tilemap::loadmapfile(const std::string_view filename) {
  std::ifstream loadfile;
  loadfile.open(std::string(filename));

  if (loadfile.is_open()) {

    loadfile >> m_maxgridsize.x >> m_maxgridsize.y >> m_gridsizei >> m_layers >>
        m_texturefilepath;
    m_gridsizef = static_cast<float>(m_gridsizei);
    m_maxmapsize.x = m_maxgridsize.x * m_gridsizef;
    m_maxmapsize.y = m_maxgridsize.y * m_gridsizef;

    clearmap();

    resizemap();

    inittexture();

    int i = 0, j = 0, k = 0, tleft = 0, tright = 0;
    bool collison = false;
    short type = tiletype::DEFALUT;

    while (loadfile >> i >> j >> k >> tleft >> tright >> collison >> type) {
      m_map[i][j][k].push_back(
          new tile(i, j, m_gridsizef, m_tilesheet,
                   sf::IntRect(tleft, tright, m_gridsizei, m_gridsizei),
                   collison, type));
    }

  } else {
    std::cout << "Error::TILEMAP::LOADMAPFILE failed to Load map in file.\n";
  }

  loadfile.close();
}

// collision
inline void tilemap::fourtilecollision(entity &entity,
                                const sf::FloatRect &playerbound,
                                const sf::FloatRect &wallbound) {
  // bottom collision
  if (playerbound.top < wallbound.top &&
      playerbound.top + playerbound.height < wallbound.top + wallbound.height &&
      playerbound.left < wallbound.left + wallbound.width &&
      playerbound.left + playerbound.width > wallbound.left) {
    entity.stopvelocity();
    entity.setposition(playerbound.left, wallbound.top - playerbound.height);
  }
  // top collison
  else if (playerbound.top > wallbound.top &&
           playerbound.top + playerbound.height >
               wallbound.top + wallbound.height &&
           playerbound.left < wallbound.left + wallbound.width &&
           playerbound.left + playerbound.width > wallbound.left) {
    entity.stopvelocity();
    entity.setposition(playerbound.left, wallbound.top + wallbound.height);
  }

  // right collision
  if (playerbound.left < wallbound.left &&
      playerbound.left + playerbound.width < wallbound.left + wallbound.width &&
      playerbound.top < wallbound.top + wallbound.height &&
      playerbound.top + playerbound.height > wallbound.top) {
    entity.stopvelocity();
    entity.setposition(wallbound.left - playerbound.width, playerbound.top);
  }
  // left collison
  else if (playerbound.left > wallbound.left &&
           playerbound.left + playerbound.width >
               wallbound.left + wallbound.width &&
           playerbound.top < wallbound.top + wallbound.height &&
           playerbound.top + playerbound.height > wallbound.top) {
    entity.stopvelocity();
    entity.setposition(wallbound.left + wallbound.width, playerbound.top);
  }
}
void tilemap::updatecollision(entity &entity, const float &dt) {

  // map collison

  if (entity.getentitypos().x < 0.f) {

    entity.setposition(0.f, entity.getentitypos().y);
    entity.stopvelocityX();

  } else if (entity.getentitypos().x + entity.getglobalbound().width >
             m_maxmapsize.x) {

    entity.setposition(m_maxmapsize.x - entity.getglobalbound().width,
                       entity.getentitypos().y);
    entity.stopvelocityX();
  }

  if (entity.getentitypos().y < 0.f) {

    entity.setposition(entity.getentitypos().x, 0.f);
    entity.stopvelocityY();

  } else if (entity.getentitypos().y + entity.getglobalbound().height >
             m_maxmapsize.y) {

    entity.setposition(entity.getentitypos().x,
                       m_maxmapsize.y - entity.getglobalbound().height);
    entity.stopvelocityY();
  }

  activegrid(entity.getgridpos(m_gridsizei));

  static sf::FloatRect playerbound;
  static sf::FloatRect wallbound;
  static sf::FloatRect playernextbound;

  for (int i = m_fromx; i < m_tox; ++i) {
    for (int j = m_fromy; j < m_toy; ++j) {
      for (int k = 0; k < m_map[i][j][m_tolayer].size(); ++k) {

        playerbound = entity.getglobalbound();
        wallbound = m_map[i][j][m_tolayer][k]->getglobalbound();
        playernextbound = entity.getnextbound(dt);

        if (m_map[i][j][m_tolayer][k]->getcollison() &&
            wallbound.intersects(playernextbound)) {
          fourtilecollision(entity, playerbound, wallbound);
        }
      }
    }
  }
}