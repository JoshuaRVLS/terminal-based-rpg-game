#include "player.hpp"
#include "weapon.hpp"
#include "weapons/spear.hpp"
#include "weapons/staff.hpp"
#include "weapons/sword.hpp"

void Player::init() {
  switch (player_class) {
  case KNIGHT:
    this->player_weapons.push_back(std::make_unique<Sword>(*this));
    break;
  case MAGE:
    this->player_weapons.push_back(std::make_unique<Staff>(*this));
    break;
  case SPEARMAN:
    this->player_weapons.push_back(std::make_unique<Spear>(*this));
    break;
  }
}

Player::Player(const std::string &display_value,
               const PlayerClass &player_class, const Position &position)
    : Sprite(display_value, 100, 100, 10, position),
      player_class(player_class) {}

PlayerClass &Player::get_class() { return player_class; }

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

void Player::set_name(const std::string &name) { this->name = name; }

void Player::set_player_coins(const int &player_coins) {
  this->player_coins = player_coins;
}

std::string &Player::get_name() { return name; }

int &Player::get_coins() { return player_coins; }
