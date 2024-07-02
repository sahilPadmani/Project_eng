#pragma once

#include "../header/skillcomponet.h"

// enum SKILLS {
//   HEALTH = 0,
//   ATTACK,
//   ACCURACY,
//   ENDURANCE,
//   SKILLCOUNT
// };

inline void skillcomponet::checkerror(const int& skill)const{
    if(skill < 0  || skill > m_skills.size())
        throw ("ERROR::SKILLCOMPONET::SKILL not include int array."); 
}

skillcomponet::skillcomponet()
{
    for(int i = 0 ; i < SKILLCOUNT ; i++){
        m_skills.at(i) = skill(i);
    }
    // this->m_skills["health"];
    // this->m_skills["endurance"];
    // this->m_skills["melee"];
    // this->m_skills["ranged"];
    // this->m_skills["accuracy"];
    // this->m_skills["defence"];
    // this->m_skills["mining"];
    // this->m_skills["woodcutting"];
}

skillcomponet::~skillcomponet()
{
    // m_skills.clear();
}



inline const int skillcomponet::getskilllevel(const int& skill)const{ 
    checkerror(skill);
    return this->m_skills.at(skill).getlevel();
}

inline void skillcomponet::gainexp(const int& skill,const int& exp){
    checkerror(skill);
    this->m_skills.at(skill).gainexp(exp);
}