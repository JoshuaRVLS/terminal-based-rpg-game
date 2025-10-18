#include "sprite.hpp"
#include "skill.hpp"

Sprite::Sprite(const std::string &display_value, const int &sprite_health,
               const int &sprite_stamina, const int &sprite_shield,
               const Position &position)
    : Object(display_value, position), sprite_health(sprite_health),
      sprite_stamina(sprite_stamina), sprite_shield(sprite_shield) {}

int &Sprite::get_sprite_health() { return sprite_health; }
int &Sprite::get_sprite_stamina() { return sprite_stamina; }
int &Sprite::get_sprite_shield() { return sprite_shield; }

void Sprite::set_sprite_health(const int &sprite_health) {
  this->sprite_health = sprite_health;
}
void Sprite::set_sprite_stamina(const int &sprite_stamina) {
  this->sprite_stamina = sprite_stamina;
}
void Sprite::set_sprite_shield(const int &sprite_shield) {
  this->sprite_shield = sprite_shield;
}

void Sprite::add_skill(std::unique_ptr<Skill> skill) {
  skills.push_back(std::move(skill));
}

void Sprite::remove_skill(int index) {
  if (index >= 0 && index < static_cast<int>(skills.size())) {
    skills.erase(skills.begin() + index);
  }
}

Skill *Sprite::get_skill(int index) {
  if (index >= 0 && index < static_cast<int>(skills.size())) {
    return skills[index].get();
  }
  return nullptr;
}

const std::vector<std::unique_ptr<Skill>> &Sprite::get_skills() const {
  return skills;
}

int Sprite::get_skill_count() const { return static_cast<int>(skills.size()); }