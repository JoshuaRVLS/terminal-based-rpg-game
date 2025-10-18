#pragma once
#include "sprite.hpp"

class Skill {

  std::string skill_name;
  std::string skill_description;
  int skill_damage;

public:
  Skill(const std::string &skill_name, const std::string &skill_description,
        const int &skill_damage);

  std::string &get_skill_name();
  std::string &get_skill_description();
  int &get_skill_damage();
};