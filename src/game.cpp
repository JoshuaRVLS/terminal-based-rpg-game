#include "utils.hpp"
#include <algorithm>
#include <conio.h>
#include <game.hpp>

void Game::start() {
  while (running) {
    utils::clear_screen();
    update();
    render();
    handle_movement();
  }
}

void Game::render() { render_map(); }

void Game::init() {
  generate_map();
  generate_player();
}

void Game::generate_player() {
  auto new_player = std::make_unique<Player>("P", Position(10, 10));
  player = new_player.get();
  maps[10][10].insert(maps[10][10].begin(), std::move(new_player));
}

void Game::handle_movement() {
  char key = _getch();
  int current_x = player->get_position().get_x();
  int current_y = player->get_position().get_y();
  int new_x = current_x;
  int new_y = current_y;

  switch (key) {
  case 'w':
    new_y--;
    break;
  case 's':
    new_y++;
    break;
  case 'a':
    new_x--;
    break;
  case 'd':
    new_x++;
    break;
  case 'q':
    exit(0);
    break;
  default:
    return;
  }

  // Boundary check
  if (new_x < 0 || new_x >= maps[0].size() || new_y < 0 ||
      new_y >= maps.size()) {
    return;
  }

  // Check if target is not a wall
  if (auto *env = dynamic_cast<Environment *>(maps[new_y][new_x][0].get())) {
    if (env->get_value() == "#") {
      return;
    }
  }

  auto &current_cell = maps[current_y][current_x];
  auto player_it =
      std::find_if(current_cell.begin(), current_cell.end(),
                   [this](const std::unique_ptr<Object> &entity) {
                     return dynamic_cast<Player *>(entity.get()) == player;
                   });

  if (player_it != current_cell.end()) {
    auto player_obj = std::move(*player_it);
    current_cell.erase(player_it);

    maps[new_y][new_x].insert(maps[new_y][new_x].begin(),
                              std::move(player_obj));
    player->get_position().set_position(new_x, new_y);
  }
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
        if (auto *p = dynamic_cast<Player *>(layer[0].get())) {
          std::cout << p->get_value();
        }
      }
    }
    std::cout << std::endl;
  }
}

Game::Game() { init(); }
