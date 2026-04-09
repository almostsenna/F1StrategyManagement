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
    std::vector<DriverProfile> driverProfiles;

    void initializeDriverProfiles();
    void showMainMenu();
    Track chooseTrack() const;
    Track applyRaceTypeToTrack(const Track& baseTrack) const;
    std::string chooseDriverName() const;
    std::string getDriverTier(const DriverProfile& driver) const;
    int findPlayerIndex() const;
    Engine createEngineForTeam(const std::string& team) const;
    F1Car createCarForProfile(const DriverProfile& profile) const;
    Strategy createStrategyForPosition(int startingPosition) const;
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

public:
    GameController();
    void run();
    void setupTestRace();
    void setupFullGridRace(const Track& selectedTrack);
    void setupRaceDirectly(int trackIndex, int driverIndex);
    void start();
    void simulateOneLap();
    void printStandings() const;
    bool isRaceFinished() const;
    void showDrivers() const;
    void showDriverBio() const;
    void chooseRaceType();
    const std::vector<DriverProfile>& getDriverProfiles() const {
        return driverProfiles;
    }
};