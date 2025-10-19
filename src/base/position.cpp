#include "position.hpp"

Position::Position(const int &x, const int &y) : x(x), y(y) {}
int &Position::get_x() { return x; }
int &Position::get_y() { return y; };

void Position::set_position(Position &position) {
  x = position.get_x();
  y = position.get_y();
}

void Position::set_position(const int &x, const int &y) {
  this->x = x;
  this->y = y;
}
