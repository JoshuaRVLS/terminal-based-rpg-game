#include "weapons/spear.hpp"

Spear::Spear(Player &weapon_owner)
    : Weapon(weapon_owner, "spear",
             "A simple, sharp point on a long stick, proving that reach is the "
             "ultimate advantage.",
             COMMON, 1, 10, 0) {}
