#include "player.hpp"
#include "skill.hpp"
#include <iostream>

Player::Player(const std::string &display_value,
               const PlayerClass &player_class, const Position &position)
    : Sprite(display_value, 100, 100, 50, position), player_class(player_class),
      player_coins(0) {
  init();
}

void Player::init() {

  switch (player_class) {
  case KNIGHT:
    sprite_health = 150;
    sprite_stamina = 80;
    sprite_shield = 30;

    add_skill(std::make_unique<Skill>("Slash", "A powerful sword slash", 25));
    add_skill(std::make_unique<Skill>("Shield Bash", "Bash with shield", 15));
    break;
  case MAGE:
    sprite_health = 80;
    sprite_stamina = 120;
    sprite_shield = 10;

    add_skill(std::make_unique<Skill>("Fireball", "Launch a fireball", 35));
    add_skill(std::make_unique<Skill>("Heal", "Restore health", -20));
    break;
  case SPEARMAN:
    sprite_health = 120;
    sprite_stamina = 100;
    sprite_shield = 20;

    add_skill(std::make_unique<Skill>("Pierce", "Pierce through armor", 20));
    add_skill(std::make_unique<Skill>("Sweep", "Sweep attack", 18));
    break;
  case LUMBERJACK:
    sprite_health = 120;
    sprite_stamina = 100;
    sprite_shield = 20;

    add_skill(
        std::make_unique<Skill>("Power Slash", "Pierce through armor", 20));
    break;
  }

  switch (player_class) {
  case KNIGHT:
    add_weapon(std::make_unique<Weapon>(
        *this, "Iron Sword", "A basic iron sword", COMMON, 50, 20, 10));
    break;
  case MAGE:
    add_weapon(std::make_unique<Weapon>(
        *this, "Wooden Staff", "A basic wooden staff", COMMON, 40, 15, 5));
    break;
  case SPEARMAN:
    add_weapon(std::make_unique<Weapon>(
        *this, "Iron Spear", "A basic iron spear", COMMON, 55, 18, 8));
    break;
  }
}

PlayerClass &Player::get_class() { return player_class; }

void Player::attack(Sprite &target, Weapon &weapon) {
  if (sprite_stamina >= 15) {
    int base_damage = weapon.get_weapon_damage();
    int final_damage = base_damage - target.get_sprite_shield();
    if (final_damage < 0)
      final_damage = 0;

    target.get_sprite_health() -= final_damage;
    sprite_stamina -= 15;

    std::cout << name << " attacks with " << weapon.get_weapon_name() << " for "
              << final_damage << " damage!" << std::endl;
  } else {
    std::cout << "Not enough stamina to attack!" << std::endl;
  }
}

void Player::use_skill(const int &skill_id) {
  if (skill_id >= 0 && skill_id < get_skill_count()) {
    Skill *skill = get_skill(skill_id);
    if (sprite_stamina >= 25) {
      std::cout << name << " uses " << skill->get_skill_name() << "!"
                << std::endl;
      std::cout << skill->get_skill_description() << std::endl;
      sprite_stamina -= 25;
    } else {
      std::cout << "Not enough stamina to use skill!" << std::endl;
    }
  } else {
    std::cout << "Invalid skill ID!" << std::endl;
  }
}

void Player::use_item(const uint8_t &item_id) {

  std::cout << "Item system not implemented yet!" << std::endl;
}

void Player::guard() {
  std::cout << name << " assumes defensive stance!" << std::endl;
  sprite_shield += 10;
  sprite_stamina -= 10;
}

void Player::set_name(const std::string &name) { this->name = name; }
void Player::set_player_coins(const int &player_coins) {
  this->player_coins = player_coins;
}

std::string &Player::get_name() { return name; }
int &Player::get_coins() { return player_coins; }

const std::vector<std::unique_ptr<Weapon>> &Player::get_weapons() const {
  return player_weapons;
}

std::vector<Weapon *> Player::get_weapons_pointers() const {
  std::vector<Weapon *> weapon_ptrs;
  for (const auto &weapon : player_weapons) {
    weapon_ptrs.push_back(weapon.get());
  }
  return weapon_ptrs;
}

void Player::add_weapon(std::unique_ptr<Weapon> weapon) {
  player_weapons.push_back(std::move(weapon));
}

void Player::remove_weapon(int index) {
  if (index >= 0 && index < static_cast<int>(player_weapons.size())) {
    player_weapons.erase(player_weapons.begin() + index);
  }
}