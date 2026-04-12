#pragma once
#include <string>
#include <vector>
#include "Race.h"
#include "DriverProfile.h"
#include "RaceType.h"

class GameController {
private:
    // Поля класу
    Race race;
    std::string playerDriverName;
    RaceType selectedRaceType;
    int customLapCount;
    std::vector<DriverProfile> driverProfiles;

    // Внутрішні методи ініціалізації
    void initializeDriverProfiles();
    void showMainMenu();

    // Методи вибору та налаштування
    Track chooseTrack() const;
    Track applyRaceTypeToTrack(const Track& baseTrack) const;
    std::string chooseDriverName() const;
    std::string getDriverTier(const DriverProfile& driver) const;
    int findPlayerIndex() const;

    // Методи створення об'єктів для гонки
    Engine createEngineForTeam(const std::string& team) const;
    F1Car createCarForProfile(const DriverProfile& profile) const;
    Strategy createStrategyForPosition(int startingPosition) const;

    // Налаштування конкретних трас (усі 10)
    Track createSilverstone() const;
    Track createMonza() const;
    Track createMonaco() const;
    Track createSpa() const;
    Track createSuzuka() const;
    Track createBahrain() const;
    Track createImola() const;
    Track createRedBullRing() const;
    Track createSingapore() const;
    Track createInterlagos() const;

    // Логіка команд гравця під час гонки
    void handlePlayerCommand();

public:
    // Конструктор
    GameController();

    // Головний цикл програми
    void run();

    // Методи підготовки до гонки
    void setupTestRace();
    void setupFullGridRace(const Track& selectedTrack);
    void setupRaceDirectly(int trackIndex, int driverIndex);

    // Керування процесом гонки
    void start();
    void simulateOneLap();
    bool isRaceFinished() const;

    // Методи виводу (інтерфейс)
    void printStandings() const;
    void showDrivers() const;
    void showDriverBio() const;
    void chooseRaceType();

    // Геттер для профілів (якщо знадобиться зовні)
    const std::vector<DriverProfile>& getDriverProfiles() const {
        return driverProfiles;
    }
};