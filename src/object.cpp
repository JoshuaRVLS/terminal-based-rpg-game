#include "object.hpp"

Object::Object(const Position &position) : position(position) {}

Position &Object::get_position() { return position; }
