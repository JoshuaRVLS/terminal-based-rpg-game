#pragma once
#include "object.hpp"
#include <string>

class Sprite;
class Object;

class Item : public Object {

  std::string item_name;
  std::string item_description;

public:
  virtual void use(Sprite &target) = 0;

  std::string getType() const override { return "Item"; }

  std::string &get_item_name();
  std::string &get_item_description();
};