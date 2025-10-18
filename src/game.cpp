#include "utils.hpp"
#include <conio.h>
#include <game.hpp>

void Game::start() {
  while (running) {
    utils::clear_screen();
    update();
    render();
    char a = getch();
    if (a == 'q') {
      running = false;
      exit(0);
    }
  }
}

void Game::render() { render_map(); }

void Game::init() {
  generate_map();
  generate_player();
}

void Game::generate_player() {
  auto new_player = std::make_unique<Player>("P", Position(1, 1));
  maps[1][1].insert(maps[1][1].begin(), std::move(new_player));
  player = std::make_unique<Player>("P", Position(1, 1));
}

void Game::update() {}

void Game::generate_map() {
  std::cout << "Generating Maps...Please wait." << std::endl;
  maps.resize(20);
  for (int i = 0; i < maps.size(); i++) {
    maps[i].resize(40);
  }

  std::cout << "Generating borders..." << std::endl;
  // Generate borders
  for (int i = 0; i < maps.size(); i++) {
    for (int j = 0; j < maps[i].size(); j++) {
      if (i == 0 || i == maps.size() - 1 || j == 0 || j == maps[i].size() - 1) {
        maps[i][j].push_back(
            std::make_unique<Environment>(Rock(Position(j, i))));
      }
    }
  }

  // generate dirt
  for (int i = 1; i < maps.size() - 1; i++) {
    for (int j = 1; j < maps[i].size() - 1; j++) {
      maps[i][j].push_back(std::make_unique<Environment>(Dirt(Position(j, i))));
    }
  }
  std::cout << "Generating map done." << std::endl;
}

void Game::render_map() {
  for (auto &row : maps) {
    for (auto &layer : row) {
      if (!layer.empty() && layer[0]) {
        if (auto *env = dynamic_cast<Environment *>(layer[0].get())) {
          std::cout << env->get_value();
        }
      }
    }
    std::cout << std::endl;
  }
}

Game::Game() { init(); }
