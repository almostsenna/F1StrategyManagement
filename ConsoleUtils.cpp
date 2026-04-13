#include "ConsoleUtils.h"
#include <windows.h>
#include <cstdlib>

void setColor(ConsoleColor color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}

void resetColor() {
    setColor(ConsoleColor::Default);
}

void clearConsole() {
    system("cls");
}

ConsoleColor getTeamColor(const std::string& team) {
    if (team == "Red Bull") return ConsoleColor::DarkRed;
    if (team == "Ferrari") return ConsoleColor::Red;
    if (team == "Mercedes") return ConsoleColor::Cyan;
    if (team == "Aston Martin") return ConsoleColor::Green;
    if (team == "Alpine") return ConsoleColor::Blue;
    if (team == "Audi") return ConsoleColor::Gray;
    if (team == "Cadillac") return ConsoleColor::White;

    if (team == "McLaren") return ConsoleColor::Yellow;
    if (team == "Williams") return ConsoleColor::Blue;
    if (team == "Haas") return ConsoleColor::White;
    if (team == "VCARB") return ConsoleColor::Cyan;

    return ConsoleColor::Default;
}

ConsoleColor getModeColor(const std::string& mode) {
    if (mode == "Push") return ConsoleColor::Red;
    if (mode == "Normal") return ConsoleColor::Yellow;
    if (mode == "Conserve") return ConsoleColor::Green;
    return ConsoleColor::Default;
}