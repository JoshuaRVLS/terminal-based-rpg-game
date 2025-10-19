#include "weapons/staff.hpp"

Staff::Staff(Player &weapon_owner)
    : Weapon(weapon_owner, "staff",
             "The world's oldest weapon, channeling the fury of the storm.",
             COMMON, 1, 10, 0) {}
