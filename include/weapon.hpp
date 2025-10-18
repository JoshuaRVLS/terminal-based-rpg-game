#pragma once
#include "sprite.hpp"
#include <string>

enum Rarity { COMMON, UNCOMMON, RARE, EPIC, LEGENDARY };

class Player;

class Weapon {
protected:
  Player &weapon_owner;
  std::string weapon_name;
  std::string weapon_description;
  Rarity weapon_rarity;
  int weapon_price;
  int weapon_damage;
  int weapon_critical_chance;

public:
  Weapon(Player &weapon_owner, const std::string &weapon_name,
         const std::string &weapon_description, const Rarity &rarity,
         const int &weapon_price, const int &weapon_damage,
         const int &weapon_critical_chance);
  ~Weapon() = default;

  void use(Sprite &target);
  void sell();

  std::string &get_weapon_name();
  std::string &get_weapon_description();
  Rarity &get_weapon_rarity();
  int &get_weapon_price();
  int &get_weapon_damage();
  int &get_weapon_critical_chance();
};