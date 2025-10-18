#pragma once
#include "position.hpp"
#include <string>

class Object {

  Position position;

public:
  Object(const Position &position);
  virtual ~Object() = default;

  Position &get_position();
  virtual std::string getType() const { return "Object"; }
};