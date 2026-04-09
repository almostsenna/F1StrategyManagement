#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include "ConsoleUI.h"
#include "GameController.h"

int main() {
    SetConsoleOutputCP(65001);
    GameController gc;

    while (true) {
        int choice = ConsoleUI::menu(
            "Formula 1 Race Strategy Simulator",
            {
                "Start New Race",
                "Show Drivers",
                "Show Driver Bio",
                "Choose Race Type",
                "Exit"
            }
        );

        // ── 0. START NEW RACE ────────────────────────────────────────────
        if (choice == 0) {

            // Вибір треку
            int trackIdx = ConsoleUI::trackMenu(
                "Choose Track",
                { "Silverstone","Monza","Monaco","Spa-Francorchamps",
                  "Suzuka","Bahrain","Imola","Red Bull Ring",
                  "Singapore","Interlagos" },
                { "5.891km | UK","5.793km | Italy","3.337km | Monaco",
                  "7.004km | Belgium","5.807km | Japan","5.412km | Bahrain",
                  "4.909km | Italy","4.318km | Austria",
                  "4.940km | Singapore","4.309km | Brazil" }
            );

            // Вибір водія
            const auto& profiles = gc.getDriverProfiles();
            std::vector<std::string> driverOptions;
            for (const auto& p : profiles) {
                driverOptions.push_back(
                    p.name + "  |  " + p.team + "  |  #" + std::to_string(p.number)
                );
            }
            int driverIdx = ConsoleUI::menu("Choose Your Driver", driverOptions);

            // Налаштовуємо гонку напряму — без fake cin
            gc.setupRaceDirectly(trackIdx, driverIdx);
            gc.start();

            // Гонка — цикл по колах
            while (!gc.isRaceFinished()) {
                // Показуємо таблицю
                ConsoleUI::clear();
                gc.printStandings();

                // Чекаємо Enter щоб гравець побачив таблицю
                ConsoleUI::println("\n  Press Enter to choose your action...", Color::BrightBlack);
                std::cin.get();

                // Вибір дії через кольорове меню
                int action = ConsoleUI::menu(
                    "Choose Your Action",
                    {
                        "Push",
                        "Normal",
                        "Conserve",
                        "Pit for Soft",
                        "Pit for Medium",
                        "Pit for Hard",
                        "Continue (no change)"
                    }
                );

                // Передаємо дію через fake cin для handlePlayerCommand
                std::string actionInput = std::to_string(action + 1) + "\n";
                std::istringstream actionStream(actionInput);
                std::streambuf* oldCin = std::cin.rdbuf(actionStream.rdbuf());
                gc.simulateOneLap();
                std::cin.rdbuf(oldCin);
            }

            // Фінальна таблиця
            ConsoleUI::clear();
            gc.printStandings();
            ConsoleUI::println("\n  *** RACE FINISHED! ***", Color::BrightYellow);
            ConsoleUI::println("\n  Press Enter to return to menu...", Color::BrightBlack);
            std::cin.get();
        }

        // ── 1. SHOW DRIVERS ──────────────────────────────────────────────
        else if (choice == 1) {
            ConsoleUI::clear();
            ConsoleUI::drawHeader("Driver List");
            gc.showDrivers();
            ConsoleUI::println("\n  Press Enter to return...", Color::BrightBlack);
            std::cin.get();
        }

        // ── 2. SHOW DRIVER BIO ───────────────────────────────────────────
        else if (choice == 2) {
            ConsoleUI::clear();
            ConsoleUI::drawHeader("Driver Bio");
            gc.showDriverBio();
            ConsoleUI::println("\n  Press Enter to return...", Color::BrightBlack);
            std::cin.get();
        }

        // ── 3. CHOOSE RACE TYPE ──────────────────────────────────────────
        else if (choice == 3) {
            int rtChoice = ConsoleUI::menu(
                "Choose Race Type",
                {
                    "Sprint  (short race)",
                    "Grand Prix  (full race)",
                    "Custom  (set your own laps)"
                }
            );

            std::string rtInput;

            if (rtChoice == 2) {
                ConsoleUI::clear();
                ConsoleUI::drawHeader("Custom Race");
                ConsoleUI::print("  Enter number of laps: ", Color::BrightCyan);
                int customLaps = 10;
                std::cin >> customLaps;
                std::cin.ignore();
                rtInput = "3\n" + std::to_string(customLaps) + "\n";
            }
            else {
                rtInput = std::to_string(rtChoice + 1) + "\n";
            }

            std::istringstream rtStream(rtInput);
            std::streambuf* oldCin = std::cin.rdbuf(rtStream.rdbuf());
            gc.chooseRaceType();
            std::cin.rdbuf(oldCin);

            ConsoleUI::println("\n  Race type updated!", Color::BrightGreen);
            Sleep(1200);
        }

        // ── 4. EXIT ──────────────────────────────────────────────────────
        else if (choice == 4) {
            ConsoleUI::clear();
            ConsoleUI::println("\n  Goodbye! See you on the track!", Color::BrightYellow);
            Sleep(1500);
            break;
        }
    }

    return 0;
}