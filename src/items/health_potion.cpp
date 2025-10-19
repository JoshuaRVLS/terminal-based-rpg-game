#include "items/health_potion.hpp"

void HealthPotion::use(Sprite &target) {
  target.set_sprite_health(target.get_sprite_health() + 20);
}