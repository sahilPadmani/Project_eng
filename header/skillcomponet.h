#pragma once

enum SKILLS {
  HEALTH = 0,
  ATTACK,
  ACCURACY,
  ENDURANCE,
  SKILLCOUNT
};

class skillcomponet {
private:
  class skill {
  private:
    int m_type;
    int m_levelcap;
    int m_level;
    int m_exp;
    int m_expnext;

    inline void setexpnext() {
      m_expnext = static_cast<int>(std::pow(m_level, 2)) + m_level * 10 + m_level * 2 + m_level;
    }

  public:
    skill() : m_type(0), m_levelcap(99), m_level(1), m_exp(0){
      setexpnext();
    }

    skill(const int &type) : m_type(type), m_levelcap(99), m_level(1), m_exp(0) {
      setexpnext();
    }

    ~skill() {}

    void operator=(const skill &other) {
      this->m_type = other.m_type;
      this->m_level = other.m_level;
      this->m_levelcap = other.m_levelcap;
      this->m_exp = other.m_exp;
      this->m_expnext = other.m_expnext;
    }

    inline const int &gettype() const { return this->m_type; }
    inline const int &getlevel() const { return this->m_level; }
    inline const int &getexp() const { return this->m_exp; }
    inline const int &getexpnext() const { return this->m_expnext; }

    inline void gainexp(const int &exp) {
      this->m_exp += exp;
      this->updatelevel(true);
    }

    inline void loseexp(const int &exp) {
      this->m_exp -= exp;
      this->updatelevel(false);
    }

    inline void setlevel(const int &level) { this->m_level = level; }
    inline void setlevelcap(const int &levelcap) { this->m_levelcap = levelcap; }

    void updatelevel(const bool &inc = true) {
      if (inc) {
        while (this->m_exp >= this->m_expnext && this->m_level < this->m_levelcap) {
          this->m_level++;
          this->m_exp -= this->m_expnext;
          setexpnext();
        }
      } else {
        while (this->m_exp < 0 && this->m_level > 0) {
          this->m_level--;
          this->m_exp += this->m_expnext;
          setexpnext();
        }
      }
    }

    void update() {}
  };

  std::array<skill, SKILLS::SKILLCOUNT> m_skills;

  //if skill not in array
  inline void checkerror(const int& skill)const;

public:
  skillcomponet();
  virtual ~skillcomponet(); // TODO: Is VIRTUAL needed?


  inline const int getskilllevel(const int &skill) const;
  inline void gainexp(const int& skill,const int& exp);
};