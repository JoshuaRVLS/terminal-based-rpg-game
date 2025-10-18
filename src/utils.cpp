#include "utils.hpp"

void utils::clear_screen() {
#ifdef __linux__
  system("clear");
#else
  system("cls");
#endif
}