#pragma once
#include <iostream>
#include <object.hpp>
#include <vector>

class Weapon;
class Item;

class Sprite : public Object {
protected:
  int sprite_health;
  int sprite_stamina;
  int sprite_shield;

public:
  Sprite(const std::string &display_value, const int &health,
         const int &stamina, const int &shield, const Position &position);
  ~Sprite() = default;

  int &get_sprite_health();
  int &get_sprite_stamina();
  int &get_sprite_shield();

  void set_sprite_health(const int &sprite_health);
  void set_sprite_stamina(const int &sprite_stamina);
  void set_sprite_shield(const int &sprite_shield);

  virtual void attack(Sprite &target, Weapon &weapon) = 0;
  virtual void use_skill(const int &skill_id) = 0;
  virtual void use_item(const uint8_t &item_id) = 0;
  virtual void guard() = 0;

  std::string getType() const override { return "Sprite"; }
};