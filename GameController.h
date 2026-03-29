#pragma once
#include "Race.h"

class GameController {
private:
    Race race;
    Track chooseTrack() const;

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

public:
    GameController();

    void setupTestRace();
    void start();
    void simulateOneLap();
    void printStandings() const;

    bool isRaceFinished() const;
};