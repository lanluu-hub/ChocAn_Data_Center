// clear_screen.h
#pragma once

#include <cstdlib>
#include <iostream>
#include <limits>

inline void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

inline void pressEnterToContinue() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clearScreen();
}
