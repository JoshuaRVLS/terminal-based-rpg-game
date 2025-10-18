#pragma once
#include "environments/dirt.hpp"
#include "environments/rock.hpp"
#include "object.hpp"
#include <iostream>
#include <memory>
#include <vector>

class Game {

  bool running = true;
  std::vector<std::vector<std::vector<std::unique_ptr<Object>>>> maps;

  void init();
  void update();
  void render();
  void generate_map();
  void render_map();

public:
  Game();
  ~Game() = default;

  void start();
};