#pragma once
#include "Race.h"

class GameController {
private:
    Race race;

public:
    GameController();

    void setupTestRace();
    void start();
    void simulateOneLap();
    void printStandings() const;

    bool isRaceFinished() const;
};