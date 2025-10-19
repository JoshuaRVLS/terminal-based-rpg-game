#include "utils.hpp"

void utils::clear_screen() {
#ifdef __linux__
  system("clear");
#else
  system("cls");
#endif
}

double utils::generateNumber(double lowerBound, double higherBound) {
  std::default_random_engine randomEngine(
      std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_real_distribution<double> generateNumber(lowerBound,
                                                        higherBound);
  return generateNumber(randomEngine);
}

#ifdef __linux__
char utils::getch() {
  struct termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);

  struct termios newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  char ch;
  read(STDIN_FILENO, &ch, 1);

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}
#endif