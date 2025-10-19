#pragma once
#include "environments/dirt.hpp"
#include "environments/rock.hpp"
#include "monster.hpp"
#include "object.hpp"
#include "player.hpp"
#include "skill.hpp"
#include "weapon.hpp"
#include <iostream>
#include <memory>
#include <vector>

class Game {
  bool running = true;
  bool game_start = false;
  bool in_battle = false;
  Player *player;
  Monster *current_monster = nullptr;
  std::vector<std::vector<std::vector<std::unique_ptr<Object>>>> maps;

  void init();
  void update();
  void render();
  void generate_map();
  void render_map();
  void generate_player(PlayerClass player_class);
  void handle_movement();
  void handle_battle_input();
  void main_menu();
  void render_info();
  void render_battle();
  void start_battle(Monster &monster);
  void end_battle(bool player_won);
  void player_attack();
  void player_use_skill();
  void player_use_item();
  void player_guard();
  void monster_turn();
  void check_battle_end();

public:
  Game();
  ~Game() = default;

  void start();
};