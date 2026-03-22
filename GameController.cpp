#include "GameController.h"
#include <iostream>
#include <iomanip>

GameController::GameController() : race() {}

void GameController::setupTestRace() {
    Track track("Silverstone", 5.891, 10, 1.2, 90.0);
    race = Race(track);

    Driver verstappen("Verstappen", 96, 94, 88);
    Driver leclerc("Leclerc", 93, 90, 85);
    Driver norris("Norris", 91, 89, 87);
    Driver hamilton("Hamilton", 95, 95, 92);

    Engine redBullPU("Honda RBPT", 950, 92);
    Engine ferrariPU("Ferrari", 945, 90);
    Engine mercedesPU("Mercedes", 940, 94);

    F1Car rbCar("RB", redBullPU, Tyre(TyreCompound::Soft), 798.0, 100.0);
    F1Car ferrariCar("Ferrari", ferrariPU, Tyre(TyreCompound::Soft), 798.0, 100.0);
    F1Car mclarenCar("McLaren", mercedesPU, Tyre(TyreCompound::Medium), 798.0, 100.0);
    F1Car mercCar("Mercedes", mercedesPU, Tyre(TyreCompound::Medium), 798.0, 100.0);

    Strategy pushStrategy(RaceMode::Push, 4);
    Strategy normalStrategy(RaceMode::Normal, 5);
    Strategy conserveStrategy(RaceMode::Conserve, 6);

    race.addParticipant(RaceEntry(verstappen, rbCar, pushStrategy));
    race.addParticipant(RaceEntry(leclerc, ferrariCar, normalStrategy));
    race.addParticipant(RaceEntry(norris, mclarenCar, normalStrategy));
    race.addParticipant(RaceEntry(hamilton, mercCar, conserveStrategy));
}

void GameController::start() {
    race.startRace();
}

void GameController::simulateOneLap() {
    race.simulateLap();
}

void GameController::printStandings() const {
    std::cout << "\n========================================\n";
    std::cout << "Lap " << race.getCurrentLap() << " / " << race.getTrack().getLaps() << "\n";
    std::cout << "Track: " << race.getTrack().getName() << "\n";
    std::cout << "========================================\n";

    for (const auto& entry : race.getParticipants()) {
        std::cout << entry.getPosition() << ". "
            << std::setw(12) << std::left << entry.getDriver().getName()
            << " | Time: " << std::fixed << std::setprecision(2) << entry.getTotalTime()
            << " | Tyre: " << entry.getCar().getTyre().getCompoundName()
            << " | Wear: " << entry.getCar().getTyre().getWear()
            << "% | Fuel: " << entry.getCar().getFuel()
            << "\n";
    }
}

bool GameController::isRaceFinished() const {
    return race.isFinished();
}