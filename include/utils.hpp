#pragma once
#include <chrono>
#include <iostream>
#include <random>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
namespace utils {

void clear_screen();
#ifdef __linux__
char getch();
#endif
double generateNumber(double lowerBound, double higherBound);
} // namespace utils