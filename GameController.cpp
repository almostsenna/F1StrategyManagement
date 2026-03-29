#include "GameController.h"
#include <iostream>
#include <iomanip>
#include <sstream>

GameController::GameController() : race() {
}
Track GameController::chooseTrack() const {
    int choice = 0;

    std::cout << "Choose track:\n";
    std::cout << "1. Silverstone\n";
    std::cout << "2. Monza\n";
    std::cout << "3. Monaco\n";
    std::cout << "4. Spa-Francorchamps\n";
    std::cout << "5. Suzuka\n";
    std::cout << "6. Bahrain\n";
    std::cout << "7. Imola\n";
    std::cout << "8. Red Bull Ring\n";
    std::cout << "9. Singapore\n";
    std::cout << "10. Interlagos\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1:  return createSilverstone();
    case 2:  return createMonza();
    case 3:  return createMonaco();
    case 4:  return createSpa();
    case 5:  return createSuzuka();
    case 6:  return createBahrain();
    case 7:  return createImola();
    case 8:  return createRedBullRing();
    case 9:  return createSingapore();
    case 10: return createInterlagos();
    default:
        std::cout << "Invalid choice. Silverstone selected by default.\n";
        return createSilverstone();
    }
}

Track GameController::createSilverstone() const {
    return Track("Silverstone", 5.891, 10, 1.2, 90.0, 1.1, 1.0, 32.0);
}

Track GameController::createMonza() const {
    return Track("Monza", 5.793, 10, 0.9, 82.0, 1.4, 0.8, 30.0);
}

Track GameController::createMonaco() const {
    return Track("Monaco", 3.337, 10, 1.4, 74.0, 0.7, 1.4, 36.0);
}

Track GameController::createSpa() const {
    return Track("Spa-Francorchamps", 7.004, 10, 1.1, 104.0, 1.2, 1.1, 28.0);
}

Track GameController::createSuzuka() const {
    return Track("Suzuka", 5.807, 10, 1.3, 88.0, 1.0, 1.3, 31.0);
}

Track GameController::createBahrain() const {
    return Track("Bahrain", 5.412, 10, 1.4, 92.0, 1.2, 1.0, 37.0);
}

Track GameController::createImola() const {
    return Track("Imola", 4.909, 10, 1.2, 86.0, 1.0, 1.2, 29.0);
}

Track GameController::createRedBullRing() const {
    return Track("Red Bull Ring", 4.318, 10, 1.0, 68.0, 1.3, 0.9, 27.0);
}

Track GameController::createSingapore() const {
    return Track("Singapore", 4.940, 10, 1.5, 102.0, 0.8, 1.3, 35.0);
}

Track GameController::createInterlagos() const {
    return Track("Interlagos", 4.309, 10, 1.2, 71.0, 1.1, 1.1, 26.0);
}

void GameController::setupTestRace() {
    Track selectedTrack = chooseTrack();

    std::cout << "\nSelected track: " << selectedTrack.getName() << "\n";
    std::cout << "Power sensitivity: " << selectedTrack.getPowerSensitivity() << "\n";
    std::cout << "Technicality: " << selectedTrack.getTechnicality() << "\n";
    std::cout << "Track temperature: " << selectedTrack.getTrackTemperature() << " C\n\n";

    race = Race(selectedTrack);

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
