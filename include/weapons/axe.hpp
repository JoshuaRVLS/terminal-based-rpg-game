#include "weapon.hpp"

class Axe : Weapon {

public:
  Axe(Player &weapon_owner, const std::string &weapon_name,
      const std::string &weapon_description, const Rarity &rarity,
      const int &weapon_price, const int &weapon_damage,
      const int &weapon_critical_chance);
};