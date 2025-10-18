#include "object.hpp"

Object::Object(const std::string &display_value, const Position &position)
    : display_value(display_value), position(position) {}

Position &Object::get_position() { return position; }
