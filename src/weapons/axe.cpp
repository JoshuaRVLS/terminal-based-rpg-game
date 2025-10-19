#include "weapons/axe.hpp"

Axe::Axe(Player &weapon_owner, const std::string &weapon_name,
         const std::string &weapon_description, const Rarity &rarity,
         const int &weapon_price, const int &weapon_damage,
         const int &weapon_critical_chance)
    : Weapon(weapon_owner, weapon_name, weapon_description, weapon_rarity,
             weapon_price, weapon_damage, weapon_critical_chance) {}