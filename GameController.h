#pragma once
#include <string>
#include <vector>
#include "Race.h"
#include "DriverProfile.h"
#include "RaceType.h"

class GameController {
private:
    Race race;
    std::string playerDriverName;
    RaceType selectedRaceType;
    int customLapCount;
    int getValidatedIntInput(int minValue, int maxValue) const;

    std::vector<DriverProfile> driverProfiles;

    void initializeDriverProfiles();
    void loadDriversFromFile(const std::string& filename);

    void showMainMenu();
    void showDrivers() const;
    void showDriverBio() const;
    void chooseRaceType();

    bool chooseTrack(Track& selectedTrack) const;
    Track applyRaceTypeToTrack(const Track& baseTrack) const;

   bool chooseDriverName(std::string& selectedDriverName) const;
    std::string getDriverTier(const DriverProfile& driver) const;
    std::string getRaceTypeName() const;
    int findPlayerIndex() const;

    Engine createEngineForTeam(const std::string& team) const;
    F1Car createCarForProfile(const DriverProfile& profile) const;
    Strategy createStrategyForPosition(int startingPosition) const;
    void setupFullGridRace(const Track& selectedTrack);

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

    void handlePlayerCommand();
    void printRaceInfoBlock() const;

public:
    GameController();

    void run();

    bool setupTestRace();
    void start();
    void simulateOneLap();
    void printStandings() const;

    bool isRaceFinished() const;
};