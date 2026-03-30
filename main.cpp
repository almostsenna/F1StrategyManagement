#include "GameController.h"
#include <iostream>

int main() {
    GameController controller;

    controller.setupTestRace();
    controller.start();

    while (!controller.isRaceFinished()) {
        controller.simulateOneLap();
        controller.printStandings();

        
    }

    std::cout << "\nRace finished!\n";
    return 0;
}