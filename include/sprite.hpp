#pragma once
#include "object.hpp"
#include <iostream>
#include <memory>
#include <vector>

class Weapon;
class Item;
class Skill;

class Sprite : public Object {
protected:
  int sprite_health;
  int sprite_stamina;
  int sprite_shield;
  std::vector<std::unique_ptr<Skill>> skills;

public:
  Sprite(const std::string &display_value, const int &health,
         const int &stamina, const int &shield, const Position &position);
  virtual ~Sprite() = default;

  int &get_sprite_health();
  int &get_sprite_stamina();
  int &get_sprite_shield();

  void set_sprite_health(const int &sprite_health);
  void set_sprite_stamina(const int &sprite_stamina);
  void set_sprite_shield(const int &sprite_shield);

  void add_skill(std::unique_ptr<Skill> skill);
  void remove_skill(int index);
  Skill *get_skill(int index);
  const std::vector<std::unique_ptr<Skill>> &get_skills() const;
  int get_skill_count() const;

  virtual void attack(Sprite &target, Weapon &weapon) = 0;
  virtual void use_skill(const int &skill_id) = 0;
  virtual void use_item(const uint8_t &item_id) = 0;
  virtual void guard() = 0;

  std::string getType() const override { return "Sprite"; }
};