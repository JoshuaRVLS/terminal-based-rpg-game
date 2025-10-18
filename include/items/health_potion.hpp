#pragma once
#include "item.hpp"
#include "sprite.hpp"

class HealthPotion : public Item {

public:
  void use(Sprite &target) override;
};