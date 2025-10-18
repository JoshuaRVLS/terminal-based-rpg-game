#pragma once

class Position {

  int x, y;

public:
  Position(const int &x, const int &y);

  int &get_x();
  int &get_y();

  void set_position(Position &position);
  void set_position(const int &x, const int &y);
};