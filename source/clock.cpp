#pragma once

#include "../preheader.hpp"

class clocktimer {
private:
  static sf::Clock staticclock;
  float pasttimefram;
public:
  clocktimer() : pasttimefram(0.f) {}
  /**
   * The function `timefram` checks if a specified time interval has passed since the last check.
   * 
   * @param time The `time` parameter in the `timefram` function represents the duration in
   * milliseconds that needs to pass before the function returns `true`.
   * 
   * @return The function `timefram` returns a boolean value indicating whether a certain time interval
   * has passed since the last time the function was called.
   */
  inline const bool timefram(const float &time) {
    float presenttime = clocktimer::staticclock.getElapsedTime().asMilliseconds();
    bool passprammeter = false;
    if ((presenttime - this->pasttimefram) >= time) {
      pasttimefram = presenttime;
      passprammeter = true;
    }
    return passprammeter;
  }
};
sf::Clock clocktimer::staticclock;