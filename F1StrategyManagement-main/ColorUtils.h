#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <windows.h>

enum F1Color {
    WHITE = 7, BLUE = 9, GREEN = 10, CYAN = 11, RED = 12, YELLOW = 14, GRAY = 8, GOLD = 6
};

inline void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

#endif