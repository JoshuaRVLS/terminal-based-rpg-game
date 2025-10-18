#pragma once
#include "item.hpp"
#include "sprite.hpp"
#include "weapon.hpp"
#include <memory>

class Player : public Sprite {

  int player_coins;
  std::vector<std::unique_ptr<Weapon>> player_weapons;
  std::vector<std::unique_ptr<Item>> player_items;

public:
  void attack(Sprite &target, Weapon &weapon) override;
  void use_skill(const int &skill_id) override;
  void use_item(const uint8_t &item_id) override;
  void guard() override;
};