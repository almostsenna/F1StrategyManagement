#include "GameController.h"
#include <iostream>
#include <iomanip>
#include <sstream>

GameController::GameController() : race() {}

void GameController::setupTestRace() {
    Track track("Silverstone", 5.891, 10, 1.2, 90.0, 1.1, 1.0, 32.0);
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

    Strategy pushStrategy(RaceMode::Push, 4, TyreCompound::Medium);
    Strategy normalStrategy(RaceMode::Normal, 5, TyreCompound::Hard);
    Strategy normalStrategy2(RaceMode::Normal, 5, TyreCompound::Hard);
    Strategy conserveStrategy(RaceMode::Conserve, 6, TyreCompound::Hard);

    race.addParticipant(RaceEntry(verstappen, rbCar, pushStrategy));
    race.addParticipant(RaceEntry(leclerc, ferrariCar, normalStrategy));
    race.addParticipant(RaceEntry(norris, mclarenCar, normalStrategy2));
    race.addParticipant(RaceEntry(hamilton, mercCar, conserveStrategy));
}

void GameController::start() {
    race.startRace();
}

void GameController::simulateOneLap() {
    race.simulateLap();
}

void GameController::printStandings() const {
    std::cout << "\n====================================================================================================\n";
    std::cout << "Lap " << race.getCurrentLap() << " / " << race.getTrack().getLaps()
        << " | Track: " << race.getTrack().getName() << "\n";
    std::cout << "====================================================================================================\n";

    const auto& participants = race.getParticipants();

    if (participants.empty()) {
        std::cout << "No participants in race.\n";
        return;
    }

    double leaderTime = participants.front().getTotalTime();

    std::cout << std::left
        << std::setw(4) << "Pos"
        << std::setw(14) << "Driver"
        << std::setw(10) << "Gap"
        << std::setw(10) << "Mode"
        << std::setw(10) << "Tyre"
        << std::setw(10) << "Wear%"
        << std::setw(10) << "TempC"
        << std::setw(10) << "Fuel"
        << std::setw(10) << "Event"
        << "\n";

    std::cout << "----------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < participants.size(); i++) {
        const auto& entry = participants[i];

        std::string gapText = (i == 0) ? "Leader"
            : "+" + std::to_string(entry.getTotalTime() - leaderTime);

        if (i != 0) {
            double gap = entry.getTotalTime() - leaderTime;
            std::ostringstream oss;
            oss << "+" << std::fixed << std::setprecision(2) << gap;
            gapText = oss.str();
        }

        std::cout << std::left
            << std::setw(4) << entry.getPosition()
            << std::setw(14) << entry.getDriver().getName()
            << std::setw(10) << gapText
            << std::setw(10) << entry.getStrategy().getModeName()
            << std::setw(10) << entry.getCar().getTyre().getCompoundName();

        std::cout << std::fixed << std::setprecision(2)
            << std::setw(10) << entry.getCar().getTyre().getWear()
            << std::setw(10) << entry.getCar().getTyre().getTemperature()
            << std::setw(10) << entry.getCar().getFuel()
            << std::setw(10) << (entry.getLastEvent().empty() ? "-" : entry.getLastEvent())
            << "\n";
    }
}

bool GameController::isRaceFinished() const {
    return race.isFinished();
}