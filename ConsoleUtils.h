#pragma once
#pragma once
#include <string>

enum class ConsoleColor {
    Default = 7,
    DarkRed = 4,
    Red = 12,
    Yellow = 14,
    Green = 10,
    Blue = 9,
    Cyan = 11,
    White = 15,
    Gray = 8
};

void setColor(ConsoleColor color);
void resetColor();
void clearConsole();

ConsoleColor getTeamColor(const std::string& team);
ConsoleColor getModeColor(const std::string& mode);