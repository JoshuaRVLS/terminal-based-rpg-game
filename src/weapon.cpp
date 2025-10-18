#include "weapon.hpp"
#include "player.hpp"

Weapon::Weapon(Player &weapon_owner, const std::string &weapon_name,
               const std::string &weapon_description, const Rarity &rarity,
               const int &weapon_price, const int &weapon_damage,
               const int &weapon_critical_chance)
    : weapon_owner(weapon_owner), weapon_name(weapon_name),
      weapon_description(weapon_description), weapon_rarity(weapon_rarity),
      weapon_price(weapon_price), weapon_damage(weapon_damage),
      weapon_critical_chance(weapon_critical_chance) {}

void Weapon::use(Sprite &target) {}

void Weapon::sell() {}

std::string &Weapon::get_weapon_name() { return weapon_name; }
std::string &Weapon::get_weapon_description() { return weapon_description; }
Rarity &Weapon::get_weapon_rarity() { return weapon_rarity; }
int &Weapon::get_weapon_price() { return weapon_price; }
int &Weapon::get_weapon_damage() { return weapon_damage; }
int &Weapon::get_weapon_critical_chance() { return weapon_critical_chance; };
