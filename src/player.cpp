#include "player.hpp"
#include "weapon.hpp"

void Player::attack(Sprite &target, Weapon &weapon) {
  int total_damage = weapon.get_weapon_damage();
  if (target.get_sprite_shield() > 0) {
    total_damage -= target.get_sprite_shield();
    target.set_sprite_shield(target.get_sprite_shield() -
                             target.get_sprite_shield());
  }
  target.set_sprite_health(target.get_sprite_health() - total_damage);
  printf("Kamu telah menyerang musuh menggunakan %s\nTotal Damage: %d",
         weapon.get_weapon_name().c_str(), weapon.get_weapon_damage());
}

void Player::use_skill(const int &skill_id) {}

void Player::use_item(const uint8_t &item_id) {}

void Player::guard() {}
