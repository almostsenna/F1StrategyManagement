#include "GameController.h"
#include "ColorUtils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

GameController::GameController() : race(),
playerDriverName("Verstappen"),
selectedRaceType(RaceType::GrandPrix),
customLapCount(10) {
    initializeDriverProfiles();
}

void GameController::showMainMenu() {
    setColor(CYAN);
    std::cout << "\n========================================\n";
    setColor(YELLOW);
    std::cout << "  Formula 1 Race Strategy Simulator\n";
    setColor(CYAN);
    std::cout << "========================================\n";
    resetColor();
    std::cout << "1. Start New Race\n2. Show Drivers\n3. Show Driver Bio\n4. Choose Race Type\n";
    setColor(RED); std::cout << "5. Exit\n"; resetColor();
    std::cout << "Enter choice: ";
}

Track GameController::chooseTrack() const {
    int choice = 0;
    std::cout << "\nChoose track (1-10):\n1. Silverstone 2. Monza 3. Monaco 4. Spa 5. Suzuka...\nChoice: ";
    std::cin >> choice; std::cin.ignore();
    switch (choice) {
    case 2: return createMonza(); case 3: return createMonaco(); case 4: return createSpa();
    default: return createSilverstone();
    }
}

std::string GameController::chooseDriverName() const {
    std::cout << "Enter driver number (1-22): ";
    int c; std::cin >> c; std::cin.ignore();
    if (c >= 1 && c <= (int)driverProfiles.size()) return driverProfiles[c - 1].name;
    return "Verstappen";
}

std::string GameController::getDriverTier(const DriverProfile& d) const {
    double avg = (d.skill + d.consistency + d.tyreManagement) / 3.0;
    if (avg >= 93) return "Elite";
    if (avg >= 88) return "Top Tier";
    return "Strong";
}

int GameController::findPlayerIndex() const {
    auto p = race.getParticipants();
    for (int i = 0; i < (int)p.size(); ++i) {
        if (p[i].getDriver().getName() == playerDriverName) return i;
    }
    return -1;
}

// Реалізація всіх трас
Track GameController::createSilverstone() const { return Track("Silverstone", 5.891, 10, 1.2, 90.0, 1.1, 1.0, 32.0); }
Track GameController::createMonza() const { return Track("Monza", 5.793, 10, 0.9, 82.0, 1.4, 0.8, 30.0); }
Track GameController::createMonaco() const { return Track("Monaco", 3.337, 10, 1.4, 74.0, 0.7, 1.4, 36.0); }
Track GameController::createSpa() const { return Track("Spa", 7.004, 10, 1.1, 104.0, 1.2, 1.1, 28.0); }
Track GameController::createSuzuka() const { return Track("Suzuka", 5.807, 10, 1.3, 88.0, 1.0, 1.3, 31.0); }
Track GameController::createBahrain() const { return Track("Bahrain", 5.412, 10, 1.4, 92.0, 1.2, 1.0, 37.0); }
Track GameController::createImola() const { return Track("Imola", 4.909, 10, 1.2, 86.0, 1.0, 1.2, 29.0); }
Track GameController::createRedBullRing() const { return Track("Red Bull Ring", 4.318, 10, 1.0, 68.0, 1.3, 0.9, 27.0); }
Track GameController::createSingapore() const { return Track("Singapore", 4.940, 10, 1.5, 102.0, 0.8, 1.3, 35.0); }
Track GameController::createInterlagos() const { return Track("Interlagos", 4.309, 10, 1.2, 71.0, 1.1, 1.1, 26.0); }

Track GameController::applyRaceTypeToTrack(const Track& b) const {
    Track m = b;
    if (selectedRaceType == RaceType::Sprint) m.setLaps(b.getLaps() / 3);
    else if (selectedRaceType == RaceType::Custom) m.setLaps(customLapCount);
    return m;
}

void GameController::run() {
    bool running = true;
    while (running) {
        showMainMenu();
        int choice; std::cin >> choice; std::cin.ignore();
        if (choice == 1) {
            setupTestRace(); start();
            while (!isRaceFinished()) { printStandings(); simulateOneLap(); }
            printStandings(); std::cout << "\nRace Finished!\n";
        }
        else if (choice == 2) showDrivers();
        else if (choice == 3) showDriverBio();
        else if (choice == 4) chooseRaceType();
        else if (choice == 5) running = false;
    }
}

void GameController::start() { race.startRace(); }
bool GameController::isRaceFinished() const { return race.isFinished(); }
void GameController::printStandings() const { race.displayStatus(); }

void GameController::simulateOneLap() {
    handlePlayerCommand();
    race.simulateLap();
}

void GameController::setupTestRace() {
    Track selectedTrack = applyRaceTypeToTrack(chooseTrack());
    playerDriverName = chooseDriverName();
    setupFullGridRace(selectedTrack);
}

void GameController::setupRaceDirectly(int tIdx, int dIdx) {
    setupFullGridRace(createSilverstone());
}

void GameController::handlePlayerCommand() {
    int idx = findPlayerIndex();
    if (idx < 0) return;
    setColor(CYAN); std::cout << "\n[1]Push [2]Normal [3]Conserve | [4]Pit Soft [5]Med [6]Hard | [7]Stay\nChoice: "; resetColor();
    int c; std::cin >> c; std::cin.ignore();
    if (c >= 1 && c <= 3) race.setParticipantMode(idx, (RaceMode)(c - 1));
    else if (c >= 4 && c <= 6) race.forcePitStop(idx, (TyreCompound)(c - 4));
}

void GameController::showDrivers() const {
    setColor(CYAN); std::cout << "\n--- DRIVER LIST ---\n"; resetColor();
    for (size_t i = 0; i < driverProfiles.size(); i++) {
        std::cout << std::left << std::setw(15) << driverProfiles[i].name << " | ";
        setColor(GOLD); std::cout << getDriverTier(driverProfiles[i]) << "\n"; resetColor();
    }
}

void GameController::showDriverBio() const {
    std::cout << "Enter driver number (1-22): ";
    int c; std::cin >> c; std::cin.ignore();
    if (c >= 1 && c <= (int)driverProfiles.size()) {
        const auto& d = driverProfiles[c - 1];
        setColor(YELLOW); std::cout << "\nProfile: " << d.name << "\n"; resetColor();
        std::cout << "Bio: " << d.bio << "\n";
    }
}

void GameController::chooseRaceType() {
    std::cout << "1. Sprint 2. GP. Choice: ";
    int c; std::cin >> c; std::cin.ignore();
    selectedRaceType = (c == 1) ? RaceType::Sprint : RaceType::GrandPrix;
}

void GameController::setupFullGridRace(const Track& t) {
    race = Race(t);
    for (const auto& p : driverProfiles) {
        Driver d(p.name, p.skill, p.consistency, p.tyreManagement);
        race.addParticipant(RaceEntry(d, createCarForProfile(p), createStrategyForPosition(p.startingPosition)));
    }
}

Engine GameController::createEngineForTeam(const std::string& t) const { return Engine("V6 Hybrid", 950, 90); }
F1Car GameController::createCarForProfile(const DriverProfile& p) const { return F1Car(p.carModel, createEngineForTeam(p.team), Tyre(TyreCompound::Medium), 798, 100); }
Strategy GameController::createStrategyForPosition(int pos) const { return Strategy(RaceMode::Normal, 5, TyreCompound::Hard); }

void GameController::initializeDriverProfiles() {
    driverProfiles.clear();
    driverProfiles = {
        {"Verstappen", "Red Bull", 1, "Netherlands", 28, 11, "Champion", "RB", "Honda RBPT", 96, 94, 88, 1},
        {"Leclerc", "Ferrari", 16, "Monaco", 28, 8, "Fast", "Ferrari", "Ferrari", 93, 90, 85, 2},
        {"Norris", "McLaren", 4, "UK", 26, 7, "Quick", "McLaren", "Mercedes", 91, 89, 87, 3},
        {"Hamilton", "Ferrari", 44, "UK", 41, 19, "Legend", "Ferrari", "Ferrari", 95, 95, 92, 4},
        {"Russell", "Mercedes", 63, "UK", 28, 7, "Consistent", "Mercedes", "Mercedes", 91, 90, 87, 5},
        {"Piastri", "McLaren", 81, "Australia", 25, 3, "Calm", "McLaren", "Mercedes", 89, 87, 86, 6},
        {"Alonso", "Aston Martin", 14, "Spain", 44, 23, "Experienced", "Aston Martin", "Honda", 92, 94, 90, 7},
        {"Antonelli", "Mercedes", 12, "Italy", 20, 1, "Rookie", "Mercedes", "Mercedes", 87, 82, 81, 8},
        {"Sainz", "Williams", 55, "Spain", 31, 11, "Intelligent", "Williams", "Mercedes", 90, 91, 88, 9},
        {"Gasly", "Alpine", 10, "France", 29, 9, "Quick", "Alpine", "Renault", 88, 87, 85, 10},
        {"Albon", "Williams", 23, "Thailand", 29, 7, "Strong", "Williams", "Mercedes", 88, 87, 86, 11},
        {"Perez", "Cadillac", 11, "Mexico", 35, 13, "Tyre Manager", "Cadillac", "Cadillac", 89, 91, 92, 12},
        {"Bottas", "Cadillac", 77, "Finland", 36, 13, "Fast", "Cadillac", "Cadillac", 88, 90, 89, 13},
        {"Ocon", "Haas", 31, "France", 29, 9, "Defensive", "Haas", "Ferrari", 87, 88, 86, 14},
        {"Hulkenberg", "Audi", 27, "Germany", 38, 13, "Dependable", "Audi", "Audi", 87, 89, 88, 15},
        {"Stroll", "Aston Martin", 18, "Canada", 27, 9, "Midfield", "Aston Martin", "Honda", 84, 83, 82, 16},
        {"Lawson", "VCARB", 30, "NZ", 24, 2, "Aggressive", "VCARB", "Honda", 84, 82, 81, 17},
        {"Colapinto", "Alpine", 43, "Argentina", 23, 2, "Exciting", "Alpine", "Renault", 85, 81, 80, 18},
        {"Bearman", "Haas", 87, "UK", 21, 1, "Potential", "Haas", "Ferrari", 84, 79, 78, 19},
        {"Bortoleto", "Audi", 5, "Brazil", 21, 1, "Rookie", "Audi", "Audi", 84, 80, 79, 20},
        {"Tsunoda", "RB", 22, "Japan", 26, 6, "Fast", "RB", "Honda", 88, 85, 84, 21},
        {"Lindblad", "VCARB", 25, "UK", 19, 1, "Highly rated", "VCARB", "Honda", 83, 78, 77, 22}
    };
}