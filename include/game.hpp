#pragma once
#include "environments/dirt.hpp"
#include "environments/rock.hpp"
#include "object.hpp"
#include "player.hpp"
#include <iostream>
#include <memory>
#include <vector>


class Game {

  bool running = true;
  std::unique_ptr<Player> player;
  std::vector<std::vector<std::vector<std::unique_ptr<Object>>>> maps;

  void init();
  void update();
  void render();
  void generate_map();
  void render_map();
  void generate_player();

public:
  Game();
  ~Game() = default;

  void start();
};