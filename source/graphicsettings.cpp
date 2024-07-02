#pragma once

#include "../header/graphicsettings.h"

 graphicssettings::graphicssettings() {
      title = "DEFULT";
      resolution = sf::VideoMode::getDesktopMode();
      fullscreen = false;
      vecSync = false;
      Framrate = 120;
      contextsettings.antialiasingLevel = 0;
      videomode = sf::VideoMode::getFullscreenModes();
    }

    void graphicssettings::savetofile(const std::string& path) {
        std::ofstream ofs(path.c_str());

      if (ofs.is_open()) {
        ofs << title <<'\n';
        ofs << resolution.width <<" " << resolution.height <<'\n';
        ofs << fullscreen <<'\n';
        ofs << Framrate <<'\n';
        ofs << vecSync <<'\n';
        ofs << contextsettings.antialiasingLevel;
      }
      ofs.close();
    }
    

    void graphicssettings::loadfromfile(const std::string&  path) {
      std::ifstream ifs(path.c_str());

      if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> resolution.width >> resolution.height;
        ifs >> fullscreen;
        ifs >> Framrate;
        ifs >> vecSync;
        ifs >> contextsettings.antialiasingLevel;
      }
      ifs.close();
    }