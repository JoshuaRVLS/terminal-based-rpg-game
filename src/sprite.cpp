#include "sprite.hpp"

Sprite::Sprite(const int &sprite_health, const int &sprite_stamina,
               const int &sprite_shield, const Position &position)
    : sprite_health(sprite_health), sprite_stamina(sprite_stamina),
      sprite_shield(sprite_shield), Object(position) {}

int &Sprite::get_sprite_health() { return sprite_health; }
int &Sprite::get_sprite_stamina() { return sprite_stamina; }
int &Sprite::get_sprite_shield() { return sprite_shield; }
void Sprite::set_sprite_health(const int &sprite_health) {
  this->sprite_health = sprite_health;
}
void Sprite::set_sprite_stamina(const int &sprite_stamina) {
  this->sprite_stamina = sprite_stamina;
}
void Sprite::set_sprite_shield(const int &sprite_shield) {
  this->sprite_shield = sprite_shield;
};