#pragma once

class graphicssettings {
public:
  std::string title;
  sf::VideoMode resolution;
  bool fullscreen;
  bool vecSync;
  unsigned Framrate;
  sf::ContextSettings contextsettings;
  std::vector<sf::VideoMode> videomode;

  graphicssettings();

  void savetofile(const std::string &path);

  void loadfromfile(const std::string &path);
};