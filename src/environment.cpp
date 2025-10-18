#include "environment.hpp"

Environment::Environment(const std::string &value, const Position &position)
    : Object(position), value(value) {}
std::string &Environment::get_value() { return value; };