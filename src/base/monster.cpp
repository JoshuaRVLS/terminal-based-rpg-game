#include "monster.hpp"
#include "skill.hpp"
#include "weapon.hpp"
#include <iostream>

Monster::Monster(const std::string &display_value, const Position &position)
    : Sprite(display_value, 100, 50, 20, position) {

  add_skill(
      std::make_unique<Skill>("Roar", "Scary roar that increases defense", 0));
  add_skill(std::make_unique<Skill>("Frenzy", "Wild attack frenzy", 25));
}

void Monster::attack(Sprite &target, Weapon &weapon) {
  if (sprite_stamina >= 10) {
    int base_damage = weapon.get_weapon_damage();
    int final_damage = base_damage - target.get_sprite_shield();
    if (final_damage < 0)
      final_damage = 0;

    target.get_sprite_health() -= final_damage;
    sprite_stamina -= 10;

    std::cout << "Monster attacks " << target.get_value() << " for "
              << final_damage << " damage!" << std::endl;
  } else {
    std::cout << "Monster is too tired to attack!" << std::endl;
  }
}

void Monster::use_skill(const int &skill_id) {
  if (skill_id >= 0 && skill_id < get_skill_count()) {
    Skill *skill = get_skill(skill_id);
    if (sprite_stamina >= 20) {
      std::cout << "Monster uses " << skill->get_skill_name() << "!"
                << std::endl;

      if (skill->get_skill_name() == "Roar") {
        sprite_shield += 10;
        std::cout << "Monster's defense increased!" << std::endl;
      } else if (skill->get_skill_name() == "Frenzy") {

        std::cout << "Monster goes into a frenzy!" << std::endl;
      }

      sprite_stamina -= 20;
    } else {
      std::cout << "Monster doesn't have enough stamina!" << std::endl;
    }
  } else {
    std::cout << "Monster uses unknown skill!" << std::endl;
  }
}

void Monster::use_item(const uint8_t &item_id) {
  std::cout << "Monster attempts to use item " << static_cast<int>(item_id)
            << " but doesn't know how!" << std::endl;
}

void Monster::guard() {
  std::cout << "Monster assumes defensive stance!" << std::endl;
  sprite_shield += 5;
}