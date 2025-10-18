#pragma once
#include "sprite.hpp"
#include <memory>

class Monster : public Sprite {
public:
  Monster(const std::string &display_value, const Position &position);

  void attack(Sprite &target, Weapon &weapon) override;
  void use_skill(const int &skill_id) override;
  void use_item(const uint8_t &item_id) override;
  void guard() override;
};