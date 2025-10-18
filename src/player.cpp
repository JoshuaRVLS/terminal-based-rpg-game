#include "player.hpp"
#include "weapon.hpp"

Player::Player(const std::string &display_value, const Position &position)
    : Sprite(display_value, 100, 100, 10, position) {}

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
