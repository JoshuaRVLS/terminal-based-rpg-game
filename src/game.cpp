#include "utils.hpp"
#include <algorithm>
#include <game.hpp>

#ifdef __linux__
#include "utils.hpp"
using namespace utils;
#endif

void Game::start() {
  while (!game_start) {
    main_menu();
  }
  while (running) {
    utils::clear_screen();
    update();
    render();

    if (in_battle) {
      handle_battle_input();
    } else {
      handle_movement();
    }
  }
}

void Game::render() {
  if (in_battle) {
    render_battle();
  } else {
    render_map();
    render_info();
  }
}

void Game::render_info() {
  std::cout << "Name: " << player->get_name() << std::endl;
  std::cout << "HP: " << player->get_sprite_health() << std::endl;
  std::cout << "Stamina: " << player->get_sprite_stamina() << std::endl;
  std::cout << "Shield: " << player->get_sprite_shield() << std::endl;
  std::cout << "Coins: " << player->get_coins() << std::endl;
  std::cout << "Press 1: Open Shop, 2: Check Inventory, 3: Check Skills"
            << std::endl;
  std::cout << "Press W: up, S: down, A: left, D: right, q = quit."
            << std::endl;
}

void Game::render_battle() {
  std::cout << "=== BATTLE ===" << std::endl;
  std::cout << player->get_name() << " vs " << current_monster->get_value()
            << std::endl;
  std::cout << "----------------------------" << std::endl;

  std::cout << player->get_name() << ":" << std::endl;
  std::cout << "  HP: " << player->get_sprite_health() << std::endl;
  std::cout << "  Stamina: " << player->get_sprite_stamina() << std::endl;
  std::cout << "  Shield: " << player->get_sprite_shield() << std::endl;

  std::cout << current_monster->get_value() << ":" << std::endl;
  std::cout << "  HP: " << current_monster->get_sprite_health() << std::endl;
  std::cout << "  Stamina: " << current_monster->get_sprite_stamina()
            << std::endl;
  std::cout << "  Shield: " << current_monster->get_sprite_shield()
            << std::endl;

  std::cout << "----------------------------" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "[1] Attack  [2] Skills  [3] Items  [4] Guard" << std::endl;
  std::cout << "Choose an action: ";
}

void Game::init() { generate_map(); }

void Game::generate_player(PlayerClass player_class) {
  auto new_player =
      std::make_unique<Player>("P", player_class, Position(10, 10));
  player = new_player.get();
  maps[10][10].insert(maps[10][10].begin(), std::move(new_player));
}

void Game::handle_movement() {
  char key = getch();
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
  case '1':
    std::cout << "Shop feature coming soon!" << std::endl;
    getch();
    return;
  case '2':
    std::cout << "Inventory: " << player->get_weapons().size() << " weapons"
              << std::endl;
    getch();
    return;
  case '3':
    std::cout << "Skills: " << player->get_skills().size() << " skills"
              << std::endl;
    for (int i = 0; i < player->get_skills().size(); i++) {
      auto skill = player->get_skills()[i].get();
      std::cout << i + 1 << ". " << skill->get_skill_name() << " - "
                << skill->get_skill_description() << std::endl;
    }
    getch();
    return;
  default:
    return;
  }

  if (new_x < 0 || new_x >= maps[0].size() || new_y < 0 ||
      new_y >= maps.size()) {
    return;
  }

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

    bool monster_encounter = false;
    Monster *encountered_monster = nullptr;

    for (auto &obj : maps[new_y][new_x]) {
      if (auto *monster = dynamic_cast<Monster *>(obj.get())) {
        monster_encounter = true;
        encountered_monster = monster;
        break;
      }
    }

    if (monster_encounter && encountered_monster) {

      start_battle(*encountered_monster);

      current_cell.insert(current_cell.begin(), std::move(player_obj));
    } else {

      maps[new_y][new_x].insert(maps[new_y][new_x].begin(),
                                std::move(player_obj));
      player->get_position().set_position(new_x, new_y);
    }
  }
}

void Game::handle_battle_input() {
  char choice = getch();
  switch (choice) {
  case '1':
    player_attack();
    break;
  case '2':
    player_use_skill();
    break;
  case '3':
    player_use_item();
    break;
  case '4':
    player_guard();
    break;
  default:
    std::cout << "Invalid choice! Press any key to continue..." << std::endl;
    getch();
    return;
  }

  check_battle_end();
  if (in_battle) {
    monster_turn();
    check_battle_end();
  }
}

void Game::start_battle(Monster &monster) {
  in_battle = true;
  current_monster = &monster;
  std::cout << "Battle started with " << monster.get_value() << "!"
            << std::endl;
  std::cout << "Press any key to continue..." << std::endl;
  getch();
}

void Game::end_battle(bool player_won) {
  in_battle = false;

  if (player_won) {
    std::cout << "Victory! You defeated the " << current_monster->get_value()
              << "!" << std::endl;

    int coins_earned = 15 + (std::rand() % 10);
    player->get_coins() += coins_earned;
    std::cout << "Earned " << coins_earned << " coins!" << std::endl;

    int monster_x = current_monster->get_position().get_x();
    int monster_y = current_monster->get_position().get_y();

    auto &cell = maps[monster_y][monster_x];
    auto monster_it = std::find_if(
        cell.begin(), cell.end(), [this](const std::unique_ptr<Object> &obj) {
          return dynamic_cast<Monster *>(obj.get()) == current_monster;
        });

    if (monster_it != cell.end()) {
      cell.erase(monster_it);
    }
  } else {
    std::cout << "You were defeated..." << std::endl;
    running = false;
  }

  current_monster = nullptr;
  std::cout << "Press any key to continue..." << std::endl;
  getch();
}

void Game::player_attack() {
  if (player->get_weapons().empty()) {
    std::cout << "You have no weapons!" << std::endl;
    return;
  }

  auto &weapon = player->get_weapons()[0];
  player->attack(*current_monster, *weapon);
}

void Game::player_use_skill() {
  if (player->get_skills().empty()) {
    std::cout << "You have no skills!" << std::endl;
    return;
  }

  utils::clear_screen();
  std::cout << "=== SKILLS ===" << std::endl;
  for (int i = 0; i < player->get_skills().size(); i++) {
    auto skill = player->get_skills()[i].get();
    std::cout << "[" << (i + 1) << "] " << skill->get_skill_name();
    std::cout << " - " << skill->get_skill_description();
    std::cout << " (Cost: 25 Stamina)" << std::endl;
  }
  std::cout << "Choose a skill (1-" << player->get_skills().size() << "): ";

  char skill_choice = getch();
  int skill_id = skill_choice - '0' - 1;

  if (skill_id >= 0 && skill_id < player->get_skills().size()) {
    player->use_skill(skill_id);

    auto skill = player->get_skills()[skill_id].get();
    if (skill->get_skill_damage() < 0) {

      std::cout << player->get_name() << " was healed!" << std::endl;
    } else {

      current_monster->get_sprite_health() -= skill->get_skill_damage();
      std::cout << "Dealt " << skill->get_skill_damage() << " damage to "
                << current_monster->get_value() << "!" << std::endl;
    }
  } else {
    std::cout << "Invalid skill choice!" << std::endl;
  }
}

void Game::player_use_item() {
  std::cout << "Item feature coming soon!" << std::endl;
}

void Game::player_guard() {
  player->guard();
  std::cout << player->get_name() << " is guarding!" << std::endl;
}

void Game::monster_turn() {
  std::cout << current_monster->get_value() << "'s turn!" << std::endl;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> action_dist(1, 100);

  int action = action_dist(gen);

  auto monster_weapon = std::make_unique<Weapon>(
      *player, "Claws", "Sharp claws", COMMON, 0, 15, 10);

  if (action <= 70) {
    current_monster->attack(*player, *monster_weapon);
  } else if (action <= 90) {
    current_monster->use_skill(0);
  } else {
    current_monster->guard();
  }
}

void Game::check_battle_end() {
  if (player->get_sprite_health() <= 0) {
    end_battle(false);
  } else if (current_monster->get_sprite_health() <= 0) {
    end_battle(true);
  }
}

void Game::main_menu() {
  std::cout << "<====================Welcome to JRPG=====================>"
            << std::endl;
  std::cout << "[1] Knight\n[2] Mage\n[3] Spearman\n[4] Lumberjack\nSelect "
               "your class: "
            << std::endl;
  char option = getch();
  switch (option) {
  case '1':
    generate_player(KNIGHT);
    break;
  case '2':
    generate_player(MAGE);
    break;
  case '3':
    generate_player(SPEARMAN);
    break;
  case '4':
    generate_player(LUMBERJACK);
    break;
  }
  std::cout << "You choose " << player->get_class()
            << " Press ENTER to continue." << std::endl;
  getch();
  utils::clear_screen();
  std::cout << "<====================Welcome to JRPG=====================>"
            << std::endl;
  std::cout << "What is your name?: ";
  std::cin >> player->get_name();
  std::cout << "Your name now is " << player->get_name() << " [ENTER]";
  getch();
  std::cout << "You ready (y/n)?";
  char key = getch();
  if (key == 'Y' || key == 'y') {
    utils::clear_screen();
    game_start = true;
  } else {
    std::cout << "NOOB!" << std::endl;
    exit(0);
  }
}

void Game::update() {

  if (!in_battle && player->get_sprite_shield() > 0) {

    player->set_sprite_shield(std::max(0, player->get_sprite_shield() - 2));
  }
}

void Game::generate_map() {
  std::cout << "Generating Maps...Please wait." << std::endl;
  maps.resize(20);
  for (int i = 0; i < maps.size(); i++) {
    maps[i].resize(40);
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(0.0, 1.0);
  std::uniform_int_distribution<> monster_dist(1, 3);

  std::cout << "Generating borders..." << std::endl;
  for (int i = 0; i < maps.size(); i++) {
    for (int j = 0; j < maps[i].size(); j++) {
      if (i == 0 || i == maps.size() - 1 || j == 0 || j == maps[i].size() - 1) {
        maps[i][j].insert(maps[i][j].begin(),
                          std::make_unique<Environment>(Rock(Position(j, i))));
      }
    }
  }

  for (int i = 1; i < maps.size() - 1; i++) {
    for (int j = 1; j < maps[i].size() - 1; j++) {
      double random_value = dist(gen);
      if (random_value < 0.2) {
        maps[i][j].insert(maps[i][j].begin(),
                          std::make_unique<Environment>(Rock(Position(j, i))));
      } else {
        maps[i][j].insert(maps[i][j].begin(),
                          std::make_unique<Environment>(Dirt(Position(j, i))));
      }
    }
  }

  int monsters_placed = 0;
  while (monsters_placed < 10) {
    int x = std::uniform_int_distribution<>(1, 38)(gen);
    int y = std::uniform_int_distribution<>(1, 18)(gen);

    if ((x >= 8 && x <= 12) && (y >= 8 && y <= 12)) {
      continue;
    }

    if (auto *env = dynamic_cast<Environment *>(maps[y][x][0].get())) {
      if (env->get_value() != "#") {
        int monster_type = monster_dist(gen);
        std::string monster_display;
        switch (monster_type) {
        case 1:
          monster_display = "G";
          break;
        case 2:
          monster_display = "O";
          break;
        case 3:
          monster_display = "S";
          break;
        default:
          monster_display = "M";
          break;
        }

        maps[y][x].insert(
            maps[y][x].begin() + 1,
            std::make_unique<Monster>(monster_display, Position(x, y)));
        monsters_placed++;
      }
    }
  }

  std::cout << "Generating map done. Placed " << monsters_placed << " monsters."
            << std::endl;
}

void Game::render_map() {
  for (auto &row : maps) {
    for (auto &layer : row) {
      if (!layer.empty()) {

        bool rendered = false;

        for (auto &obj : layer) {
          if (auto *p = dynamic_cast<Player *>(obj.get())) {
            std::cout << p->get_value();
            rendered = true;
            break;
          }
        }

        if (!rendered) {
          for (auto &obj : layer) {
            if (auto *m = dynamic_cast<Monster *>(obj.get())) {
              std::cout << m->get_value();
              rendered = true;
              break;
            }
          }
        }

        if (!rendered && layer[0]) {
          if (auto *env = dynamic_cast<Environment *>(layer[0].get())) {
            std::cout << env->get_value();
          }
        }
      }
    }
    std::cout << std::endl;
  }
}

Game::Game() { init(); }