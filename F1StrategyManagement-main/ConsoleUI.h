// ConsoleUI.h
#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

enum class Color {
    Black = 0, Blue = 1, Green = 2, Cyan = 3,
    Red = 4, Magenta = 5, Yellow = 6, White = 7,
    BrightBlack = 8, BrightBlue = 9, BrightGreen = 10,
    BrightCyan = 11, BrightRed = 12, BrightMagenta = 13,
    BrightYellow = 14, BrightWhite = 15
};

class ConsoleUI {
public:
    static void setColor(Color fg, Color bg = Color::Black) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, (int)bg * 16 + (int)fg);
    }

    static void resetColor() {
        setColor(Color::White, Color::Black);
    }

    static void clear() {
        system("cls");
    }

    static void hideCursor() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO ci;
        ci.dwSize = 1;
        ci.bVisible = FALSE;
        SetConsoleCursorInfo(h, &ci);
    }

    static void showCursor() {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO ci;
        ci.dwSize = 10;
        ci.bVisible = TRUE;
        SetConsoleCursorInfo(h, &ci);
    }

    static void drawHeader(const std::string& title) {
        std::string border(title.size() + 4, '=');
        setColor(Color::BrightYellow);
        std::cout << "\n  " << border << "\n";
        std::cout << "  | ";
        setColor(Color::BrightWhite);
        std::cout << title;
        setColor(Color::BrightYellow);
        std::cout << " |\n";
        std::cout << "  " << border << "\n\n";
        resetColor();
    }

    static int menu(const std::string& title, const std::vector<std::string>& options) {
        hideCursor();
        int selected = 0;
        int n = (int)options.size();

        // Кольори для кожного пункту меню
        std::vector<Color> itemColors = {
            Color::BrightRed,
            Color::BrightYellow,
            Color::BrightGreen,
            Color::BrightCyan,
            Color::BrightMagenta,
            Color::BrightBlue,
            Color::BrightRed,
            Color::BrightYellow,
            Color::BrightGreen,
            Color::BrightCyan
        };

        while (true) {
            clear();
            drawHeader(title);

            // Підказка тільки англійською
            setColor(Color::BrightBlack);
            std::cout << "  Use ";
            setColor(Color::BrightCyan);
            std::cout << "[W/S]";
            setColor(Color::BrightBlack);
            std::cout << " or ";
            setColor(Color::BrightCyan);
            std::cout << "[arrows]";
            setColor(Color::BrightBlack);
            std::cout << " to navigate, ";
            setColor(Color::BrightGreen);
            std::cout << "[Enter]";
            setColor(Color::BrightBlack);
            std::cout << " to select\n\n";
            resetColor();

            for (int i = 0; i < n; i++) {
                Color c = itemColors[i % itemColors.size()];

                if (i == selected) {
                    // Стрілка + підсвічений текст на темному фоні
                    setColor(c);
                    std::cout << "   >> ";
                    setColor(c, Color::Blue); // текст кольоровий, фон синій
                    std::cout << " " << options[i] << " ";
                    resetColor();
                    std::cout << "\n";
                }
                else {
                    // Звичайний пункт — свій колір але без фону
                    setColor(Color::BrightBlack);
                    std::cout << "      ";
                    setColor(c);
                    std::cout << options[i] << "\n";
                    resetColor();
                }
            }

            std::cout << "\n";

            int key = _getch();
            if (key == 0 || key == 224) {
                key = _getch();
                if (key == 72) selected = (selected - 1 + n) % n; // вгору
                if (key == 80) selected = (selected + 1) % n;     // вниз
            }
            else {
                if (key == 'w' || key == 'W') selected = (selected - 1 + n) % n;
                if (key == 's' || key == 'S') selected = (selected + 1) % n;
                if (key == 13) break; // Enter
            }
        }

        showCursor();
        return selected;
    }

    static int trackMenu(const std::string& title,
        const std::vector<std::string>& tracks,
        const std::vector<std::string>& infos) {
        hideCursor();
        int selected = 0;
        int n = (int)tracks.size();

        std::vector<Color> itemColors = {
            Color::BrightRed, Color::BrightYellow, Color::BrightGreen,
            Color::BrightCyan, Color::BrightMagenta, Color::BrightBlue,
            Color::BrightRed, Color::BrightYellow, Color::BrightGreen,
            Color::BrightCyan
        };

        while (true) {
            clear();
            drawHeader(title);

            setColor(Color::BrightBlack);
            std::cout << "  Use [W/S or arrows] to navigate, [Enter] to select\n\n";
            resetColor();

            for (int i = 0; i < n; i++) {
                Color c = itemColors[i % itemColors.size()];

                if (i == selected) {
                    setColor(c);
                    std::cout << "   >> ";
                    setColor(c, Color::Blue);
                    std::cout << " " << tracks[i];
                    if (i < (int)infos.size()) {
                        std::cout << "  (" << infos[i] << ")";
                    }
                    std::cout << " ";
                    resetColor();
                    std::cout << "\n";
                }
                else {
                    setColor(Color::BrightBlack);
                    std::cout << "      ";
                    setColor(c);
                    std::cout << tracks[i];
                    if (i < (int)infos.size()) {
                        setColor(Color::BrightBlack);
                        std::cout << "  (" << infos[i] << ")";
                    }
                    std::cout << "\n";
                    resetColor();
                }
            }

            std::cout << "\n";

            int key = _getch();
            if (key == 0 || key == 224) {
                key = _getch();
                if (key == 72) selected = (selected - 1 + n) % n;
                if (key == 80) selected = (selected + 1) % n;
            }
            else {
                if (key == 'w' || key == 'W') selected = (selected - 1 + n) % n;
                if (key == 's' || key == 'S') selected = (selected + 1) % n;
                if (key == 13) break;
            }
        }

        showCursor();
        return selected;
    }

    static void pause(const std::string& msg = "Press Enter to continue...") {
        setColor(Color::BrightBlack);
        std::cout << "\n  " << msg;
        resetColor();
        std::cin.ignore();
        std::cin.get();
    }

    static void print(const std::string& text, Color c = Color::White) {
        setColor(c);
        std::cout << text;
        resetColor();
    }

    static void println(const std::string& text, Color c = Color::White) {
        setColor(c);
        std::cout << text << "\n";
        resetColor();
    }
};