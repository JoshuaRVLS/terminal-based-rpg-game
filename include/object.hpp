#pragma once
#include "position.hpp"
#include <string>

class Object {

  Position position;
  std::string display_value;

public:
  Object(const std::string &display_value, const Position &position);
  virtual ~Object() = default;

  Position &get_position();

  std::string &get_value() { return display_value; };

  virtual std::string getType() const { return "Object"; }
};