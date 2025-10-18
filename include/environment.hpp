#pragma once
#include "object.hpp"
#include <string>

class Environment : public Object {

public:
  Environment(const std::string &display_value, const Position &position);

  std::string getType() const override { return "Environment"; }
};