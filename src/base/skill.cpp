#include "skill.hpp"

Skill::Skill(const std::string &skill_name,
             const std::string &skill_description, const int &skill_damage)
    : skill_name(skill_name), skill_description(skill_description),
      skill_damage(skill_damage) {}

std::string &Skill::get_skill_name() { return skill_name; }

std::string &Skill::get_skill_description() { return skill_description; }

int &Skill::get_skill_damage() { return skill_damage; }
