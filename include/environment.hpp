#pragma once
#include "object.hpp"
#include <string>

class Environment : public Object {

  std::string value;

public:
  Environment(const std::string &value, const Position &position);

  std::string &get_value();

  std::string getType() const override { return "Environment"; }
};