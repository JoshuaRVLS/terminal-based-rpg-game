#include "weapons/sword.hpp"

Sword::Sword(Player &weapon_owner)
    : Weapon(weapon_owner, "sword", "Sword is dangerous", COMMON, 1, 10, 0) {};
