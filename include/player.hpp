#pragma once
#include "item.hpp"
#include "sprite.hpp"
#include "weapon.hpp"
#include <memory>

enum PlayerClass { KNIGHT, MAGE, SPEARMAN };

class Player : public Sprite {

  std::string name;
  PlayerClass player_class;
  int player_coins;
  std::vector<std::unique_ptr<Weapon>> player_weapons;
  std::vector<std::unique_ptr<Item>> player_items;

  void init();

public:
  Player(const std::string &display_value, const PlayerClass &player_class,
         const Position &position);

  PlayerClass &get_class();

  void attack(Sprite &target, Weapon &weapon) override;
  void use_skill(const int &skill_id) override;
  void use_item(const uint8_t &item_id) override;
  void guard() override;

  void set_name(const std::string &name);
  void set_player_coins(const int &player_coins);

  std::string &get_name();
  int &get_coins();
};