#include "GameController.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <limits>

GameController::GameController() 
  : race(),
    playerDriverName("Verstappen"),
    selectedRaceType(RaceType::GrandPrix),
    customLapCount(10) {
   initializeDriverProfiles();
}

int GameController::getValidatedIntInput(int minValue, int maxValue) const {
    int value;

    while (true) {
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number from "
                << minValue << " to " << maxValue << ": ";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value < minValue || value > maxValue) {
            std::cout << "Choice out of range. Enter a number from "
                << minValue << " to " << maxValue << ": ";
            continue;
        }

        return value;
    }
}

void GameController::showMainMenu() {
    clearConsole();

    setColor(ConsoleColor::Yellow);
    std::cout << "\n====================================================\n";
    std::cout << "           Formula 1 Strategy Management            \n";
    std::cout << "====================================================\n";
    resetColor();

    setColor(ConsoleColor::Cyan);
    std::cout << "1. Start New Race\n";
    std::cout << "2. Show Drivers\n";
    std::cout << "3. Show Driver Bio\n";
    std::cout << "4. Choose Race Type\n";
    resetColor();

    setColor(ConsoleColor::Red);
    std::cout << "5. Exit\n";
    resetColor();

    std::cout << "Enter choice: ";
}

bool GameController::chooseTrack(Track& selectedTrack) const {
    while (true) {
        clearConsole();

        setColor(ConsoleColor::Yellow);
        std::cout << "==================== CHOOSE TRACK ====================\n";
        resetColor();

        setColor(ConsoleColor::Cyan);
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
        resetColor();

        std::cout << "0. Back\n";
        std::cout << "Enter choice: ";

        int choice = getValidatedIntInput(0, 10);

        switch (choice) {
        case 0:  return false;
        case 1:  selectedTrack = createSilverstone(); return true;
        case 2:  selectedTrack = createMonza(); return true;
        case 3:  selectedTrack = createMonaco(); return true;
        case 4:  selectedTrack = createSpa(); return true;
        case 5:  selectedTrack = createSuzuka(); return true;
        case 6:  selectedTrack = createBahrain(); return true;
        case 7:  selectedTrack = createImola(); return true;
        case 8:  selectedTrack = createRedBullRing(); return true;
        case 9:  selectedTrack = createSingapore(); return true;
        case 10: selectedTrack = createInterlagos(); return true;
        default:
            break;
        }
    }
}

std::string GameController::getRaceTypeName() const {
    switch (selectedRaceType) {
    case RaceType::Sprint:
        return "Sprint";
    case RaceType::GrandPrix:
        return "Grand Prix";
    case RaceType::Custom:
        return "Custom";
    default:
        return "Unknown";
    }
}

bool GameController::chooseDriverName(std::string& selectedDriverName) const {
    if (driverProfiles.empty()) {
        std::cout << "No drivers available.\n";
        system("pause");
        return false;
    }

    while (true) {
        clearConsole();

        setColor(ConsoleColor::Yellow);
        std::cout << "==================== CHOOSE DRIVER ====================\n";
        resetColor();

        for (size_t i = 0; i < driverProfiles.size(); i++) {
            const auto& d = driverProfiles[i];

            setColor(ConsoleColor::Cyan);
            std::cout << std::setw(2) << (i + 1) << ". ";
            resetColor();

            setColor(getTeamColor(d.team));
            std::cout << std::setw(12) << std::left << d.name;
            resetColor();

            std::cout << " | Team: " << std::setw(15) << d.team
                << " | #" << d.number
                << " | Tier: " << getDriverTier(d)
                << "\n";
        }

        std::cout << "0. Back\n";
        std::cout << "Enter choice: ";

        int choice = getValidatedIntInput(0, static_cast<int>(driverProfiles.size()));

        if (choice == 0) {
            return false;
        }

        selectedDriverName = driverProfiles[choice - 1].name;
        return true;
    }
}

std::string GameController::getDriverTier(const DriverProfile& driver) const {
    double average = (driver.skill + driver.consistency + driver.tyreManagement) / 3.0;

    if (average >= 93.0) return "Elite";
    if (average >= 88.0) return "Top Tier";
    if (average >= 82.0) return "Strong";
    return "Developing";
}

int GameController::findPlayerIndex() const {
    const auto& participants = race.getParticipants();

    for (size_t i = 0; i < participants.size(); i++) {
        if (participants[i].getDriver().getName() == playerDriverName) {
            return static_cast<int>(i);
        }
    }

    return -1;
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

Track GameController::applyRaceTypeToTrack(const Track& baseTrack) const {
    Track modifiedTrack = baseTrack;

    switch (selectedRaceType) {
    case RaceType::Sprint: {
        int sprintLaps = baseTrack.getLaps() / 3;
        if (sprintLaps < 1) sprintLaps = 1;
        modifiedTrack.setLaps(sprintLaps);
        break;
    }
    case RaceType::GrandPrix:
        // залишаємо стандартну кількість кіл
        break;
    case RaceType::Custom:
        modifiedTrack.setLaps(customLapCount);
        break;
    default:
        break;
    }

    return modifiedTrack;
}

bool GameController::setupTestRace() {
    Track baseTrack;
    if (!chooseTrack(baseTrack)) {
        return false;
    }

    Track selectedTrack = applyRaceTypeToTrack(baseTrack);

    std::string selectedDriverName;
    if (!chooseDriverName(selectedDriverName)) {
        return false;
    }

    playerDriverName = selectedDriverName;

    clearConsole();

    setColor(ConsoleColor::Yellow);
    std::cout << "=========================== RACE SETUP ===========================\n";
    resetColor();

    std::cout << "Selected track    : " << selectedTrack.getName() << "\n";
    std::cout << "Race type         : " << getRaceTypeName() << "\n";
    std::cout << "Laps              : " << selectedTrack.getLaps() << "\n";
    std::cout << "Power sensitivity : " << selectedTrack.getPowerSensitivity() << "\n";
    std::cout << "Technicality      : " << selectedTrack.getTechnicality() << "\n";
    std::cout << "Track temperature : " << selectedTrack.getTrackTemperature() << " C\n";
    std::cout << "Your driver       : " << playerDriverName << "\n";
    std::cout << "==================================================================\n\n";

    setupFullGridRace(selectedTrack);
    system("pause");
    return true;
}

void GameController::start() {
    race.startRace();
}

void GameController::handlePlayerCommand() {
    int playerIndex = findPlayerIndex();
    const auto& participants = race.getParticipants();

    if (playerIndex < 0 || playerIndex >= static_cast<int>(participants.size())) {
        return;
    }

    clearConsole();
    printStandings();

    std::cout << "\nYour driver: " << participants[playerIndex].getDriver().getName() << "\n";
    std::cout << "Choose action:\n";

    setColor(ConsoleColor::Red);
    std::cout << "1. Push\n";
    resetColor();

    setColor(ConsoleColor::Yellow);
    std::cout << "2. Normal\n";
    resetColor();

    setColor(ConsoleColor::Green);
    std::cout << "3. Conserve\n";
    resetColor();

    std::cout << "4. Pit for Soft\n";
    std::cout << "5. Pit for Medium\n";
    std::cout << "6. Pit for Hard\n";
    std::cout << "7. Continue\n";
    std::cout << "Enter choice: ";

    int choice = getValidatedIntInput(1, 7);

    switch (choice) {
    case 1:
        race.setParticipantMode(playerIndex, RaceMode::Push);
        break;
    case 2:
        race.setParticipantMode(playerIndex, RaceMode::Normal);
        break;
    case 3:
        race.setParticipantMode(playerIndex, RaceMode::Conserve);
        break;
    case 4:
        race.forcePitStop(playerIndex, TyreCompound::Soft);
        break;
    case 5:
        race.forcePitStop(playerIndex, TyreCompound::Medium);
        break;
    case 6:
        race.forcePitStop(playerIndex, TyreCompound::Hard);
        break;
    case 7:
    default:
        break;
    }
}

void GameController::simulateOneLap() {
    handlePlayerCommand();
    race.simulateLap();
}

void GameController::printStandings() const {
    clearConsole();

    setColor(ConsoleColor::Yellow);
    std::cout << "=====================================================================\n";
    std::cout << "Lap " << race.getCurrentLap() << " / " << race.getTrack().getLaps()
        << " | Track: " << race.getTrack().getName() << "\n";
    std::cout << "=====================================================================\n";
    resetColor();

    printRaceInfoBlock();

    const auto& participants = race.getParticipants();

    if (participants.empty()) {
        std::cout << "No participants in race.\n";
        return;
    }

    double leaderTime = participants.front().getTotalTime();

    setColor(ConsoleColor::Yellow);
    std::cout << std::left
        << std::setw(4) << "Pos"
        << std::setw(20) << "Driver"
        << std::setw(10) << "Gap"
        << std::setw(10) << "Mode"
        << std::setw(10) << "Tyre"
        << std::setw(10) << "Wear%"
        << std::setw(10) << "TempC"
        << std::setw(10) << "Fuel"
        << std::setw(14) << "Event"
        << "\n";
    resetColor();

    std::cout << "------------------------------------------------------------------------"
        "----------------------------\n";

    for (size_t i = 0; i < participants.size(); i++) {
        const auto& entry = participants[i];

        std::string driverName = entry.getDriver().getName();
        if (entry.getDriver().getName() == playerDriverName) {
            driverName += " [YOU]";
        }

        std::string gapText = "Leader";
        if (i != 0) {
            double gap = entry.getTotalTime() - leaderTime;
            std::ostringstream oss;
            oss << "+" << std::fixed << std::setprecision(2) << gap;
            gapText = oss.str();
        }

        std::cout << std::left << std::setw(4) << entry.getPosition();

        if (entry.getDriver().getName() == playerDriverName) {
            setColor(ConsoleColor::Yellow);
        }
        else {
            resetColor();
        }

        std::cout << std::setw(20) << driverName;
        resetColor();

        std::cout << std::setw(10) << gapText;

        std::string modeName = entry.getStrategy().getModeName();
        setColor(getModeColor(modeName));
        std::cout << std::setw(10) << modeName;
        resetColor();

        std::cout << std::setw(10) << entry.getCar().getTyre().getCompoundName();

        std::cout << std::fixed << std::setprecision(2)
            << std::setw(10) << entry.getCar().getTyre().getWear()
            << std::setw(10) << entry.getCar().getTyre().getTemperature()
            << std::setw(10) << entry.getCar().getFuel()
            << std::setw(14) << (entry.getLastEvent().empty() ? "-" : entry.getLastEvent())
            << "\n";
    }
}

bool GameController::isRaceFinished() const {
    return race.isFinished();
}

void GameController::initializeDriverProfiles() {
    loadDriversFromFile("drivers.csv");
}

void GameController::loadDriversFromFile(const std::string& filename) {
    driverProfiles.clear();

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << "\n";
        return;
    }

    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        DriverProfile d;

        std::getline(ss, d.name, ',');
        std::getline(ss, d.team, ',');

        std::getline(ss, token, ',');
        d.number = std::stoi(token);

        std::getline(ss, d.nationality, ',');

        std::getline(ss, token, ',');
        d.age = std::stoi(token);

        std::getline(ss, token, ',');
        d.experienceYears = std::stoi(token);

        std::getline(ss, d.bio, ',');
        std::getline(ss, d.carModel, ',');
        std::getline(ss, d.engineName, ',');

        std::getline(ss, token, ',');
        d.skill = std::stoi(token);

        std::getline(ss, token, ',');
        d.consistency = std::stoi(token);

        std::getline(ss, token, ',');
        d.tyreManagement = std::stoi(token);

        std::getline(ss, token, ',');
        d.startingPosition = std::stoi(token);

        driverProfiles.push_back(d);
    }

    file.close();
}
void GameController::showDrivers() const {
    while (true) {
        clearConsole();

        setColor(ConsoleColor::Yellow);
        std::cout << "\n============================== DRIVER LIST ==============================\n";
        resetColor();

        std::cout << std::left
            << std::setw(4) << "No"
            << std::setw(15) << "Driver"
            << std::setw(15) << "Team"
            << std::setw(8) << "#"
            << std::setw(15) << "Nation"
            << std::setw(12) << "Tier"
            << "\n";

        std::cout << "-------------------------------------------------------------------------\n";

        for (size_t i = 0; i < driverProfiles.size(); i++) {
            const auto& d = driverProfiles[i];

            std::cout << std::left << std::setw(4) << (i + 1);

            setColor(getTeamColor(d.team));
            std::cout << std::setw(15) << d.name
                << std::setw(15) << d.team;
            resetColor();

            std::cout << std::setw(8) << d.number
                << std::setw(15) << d.nationality
                << std::setw(12) << getDriverTier(d)
                << "\n";
        }

        std::cout << "=========================================================================\n";
        std::cout << "0. Back\n";
        std::cout << "Enter 0 to return: ";

        int back = 0;
        std::cin >> back;
        std::cin.ignore();
        return;
    }
}

void GameController::showDriverBio() const {
    if (driverProfiles.empty()) {
        std::cout << "\nNo drivers available.\n";
        return;
    }

    while (true) {
        clearConsole();

        setColor(ConsoleColor::Yellow);
        std::cout << "\n========================= CHOOSE DRIVER BIO =========================\n";
        resetColor();

        for (size_t i = 0; i < driverProfiles.size(); i++) {
            setColor(ConsoleColor::Cyan);
            std::cout << i + 1 << ". ";
            resetColor();

            setColor(getTeamColor(driverProfiles[i].team));
            std::cout << driverProfiles[i].name;
            resetColor();

            std::cout << " (" << driverProfiles[i].team << ")\n";
        }

        std::cout << "0. Back\n";
        std::cout << "Enter choice: ";

        int choice = 0;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) {
            return;
        }

        if (choice < 1 || choice > static_cast<int>(driverProfiles.size())) {
            std::cout << "Invalid choice.\n";
            system("pause");
            continue;
        }

        clearConsole();

        const auto& d = driverProfiles[choice - 1];

        setColor(getTeamColor(d.team));
        std::cout << "\n=========================== DRIVER PROFILE ===========================\n";
        std::cout << d.name << "  (#" << d.number << ")\n";
        resetColor();

        std::cout << "---------------------------------------------------------------------\n";
        std::cout << "Team           : " << d.team << "\n";
        std::cout << "Nationality    : " << d.nationality << "\n";
        std::cout << "Age            : " << d.age << "\n";
        std::cout << "Experience     : " << d.experienceYears << " years\n";
        std::cout << "Car            : " << d.carModel << "\n";
        std::cout << "Engine         : " << d.engineName << "\n";
        std::cout << "Tier           : " << getDriverTier(d) << "\n";
        std::cout << "---------------------------------------------------------------------\n";
        std::cout << "Skill          : " << d.skill << "\n";
        std::cout << "Consistency    : " << d.consistency << "\n";
        std::cout << "Tyre Management: " << d.tyreManagement << "\n";
        std::cout << "---------------------------------------------------------------------\n";
        std::cout << "Bio            : " << d.bio << "\n";
        std::cout << "=====================================================================\n";

        std::cout << "\n0. Back\n";
        int back = 0;
        std::cin >> back;
        std::cin.ignore();
    }
}

void GameController::chooseRaceType() {
    while (true) {
        clearConsole();

        setColor(ConsoleColor::Yellow);
        std::cout << "\n======================== CHOOSE RACE TYPE ========================\n";
        resetColor();

        setColor(ConsoleColor::Cyan);
        std::cout << "1. Sprint\n";
        std::cout << "2. Grand Prix\n";
        std::cout << "3. Custom\n";
        resetColor();

        std::cout << "0. Back\n";
        std::cout << "Enter choice: ";

        int choice = getValidatedIntInput(0, 3);

        if (choice == 0) {
            return;
        }

        switch (choice) {
        case 1:
            selectedRaceType = RaceType::Sprint;
            clearConsole();
            std::cout << "Race type updated: Sprint\n";
            system("pause");
            return;

        case 2:
            selectedRaceType = RaceType::GrandPrix;
            clearConsole();
            std::cout << "Race type updated: Grand Prix\n";
            system("pause");
            return;

        case 3:
            selectedRaceType = RaceType::Custom;
            std::cout << "Enter custom lap count: ";
            customLapCount = getValidatedIntInput(1, 200);

            if (customLapCount <= 0) {
                customLapCount = 10;
            }

            clearConsole();
            std::cout << "Race type updated: Custom (" << customLapCount << " laps)\n";
            system("pause");
            return;

        default:
            std::cout << "Invalid choice.\n";
            system("pause");
            break;
        }
    }
}

void GameController::run() {
    bool running = true;

    while (running) {
        showMainMenu();

        int choice = getValidatedIntInput(1, 5);

        switch (choice) {
        case 1:
            if (!setupTestRace()) {
                break;
            }

            start();

            while (!isRaceFinished()) {
                printStandings();
                simulateOneLap();
            }

            printStandings();
            std::cout << "\nRace finished!\n";
            system("pause");
            break;

        case 2:
            showDrivers();
            break;

        case 3:
            showDriverBio();
            break;

        case 4:
            chooseRaceType();
            break;

        case 5:
            running = false;
            clearConsole();
            std::cout << "Exiting program...\n";
            break;
        }
    }
}

Engine GameController::createEngineForTeam(const std::string& team) const {
    if (team == "Red Bull" || team == "VCARB") {
        return Engine("Honda RBPT", 950, 92);
    }
    if (team == "Ferrari" || team == "Haas") {
        return Engine("Ferrari", 945, 90);
    }
    if (team == "Mercedes" || team == "McLaren" || team == "Williams") {
        return Engine("Mercedes", 940, 94);
    }
    if (team == "Aston Martin") {
        return Engine("Honda", 944, 91);
    }
    if (team == "Alpine") {
        return Engine("Renault", 930, 88);
    }
    if (team == "Audi") {
        return Engine("Audi", 936, 89);
    }
    if (team == "Cadillac") {
        return Engine("Cadillac PU", 938, 90);
    }

    return Engine("Generic Engine", 900, 85);
}

F1Car GameController::createCarForProfile(const DriverProfile& profile) const {
    Engine engine = createEngineForTeam(profile.team);

    TyreCompound startCompound = TyreCompound::Medium;

    if (profile.startingPosition <= 6) {
        startCompound = TyreCompound::Soft;
    }
    else if (profile.startingPosition <= 14) {
        startCompound = TyreCompound::Medium;
    }
    else {
        startCompound = TyreCompound::Hard;
    }

    return F1Car(
        profile.carModel,
        engine,
        Tyre(startCompound),
        798.0,
        100.0
    );
}

Strategy GameController::createStrategyForPosition(int startingPosition) const {
    if (startingPosition <= 4) {
        return Strategy(RaceMode::Push, 4, TyreCompound::Medium);
    }
    else if (startingPosition <= 10) {
        return Strategy(RaceMode::Normal, 5, TyreCompound::Hard);
    }
    else if (startingPosition <= 16) {
        return Strategy(RaceMode::Normal, 6, TyreCompound::Hard);
    }
    else {
        return Strategy(RaceMode::Conserve, 7, TyreCompound::Medium);
    }
}
void GameController::setupFullGridRace(const Track& selectedTrack) {
    race = Race(selectedTrack);

    std::vector<DriverProfile> sortedProfiles = driverProfiles;

    std::sort(sortedProfiles.begin(), sortedProfiles.end(),
        [](const DriverProfile& a, const DriverProfile& b) {
            return a.startingPosition < b.startingPosition;
        });

    for (const auto& profile : sortedProfiles) {
        Driver driver(
            profile.name,
            profile.skill,
            profile.consistency,
            profile.tyreManagement
        );

        F1Car car = createCarForProfile(profile);
        Strategy strategy = createStrategyForPosition(profile.startingPosition);

        race.addParticipant(RaceEntry(driver, car, strategy));
    }
}

void GameController::printRaceInfoBlock() const {
    setColor(ConsoleColor::Yellow);
    std::cout << "============================== RACE INFO ==============================\n";
    resetColor();

    std::cout << "Track        : " << race.getTrack().getName() << "\n";
    std::cout << "Race Type    : " << getRaceTypeName() << "\n";
    std::cout << "Laps         : " << race.getTrack().getLaps() << "\n";
    std::cout << "Temperature  : " << race.getTrack().getTrackTemperature() << " C\n";
    std::cout << "Driver       : " << playerDriverName << "\n";

    int playerIndex = findPlayerIndex();
    if (playerIndex >= 0 && playerIndex < static_cast<int>(race.getParticipants().size())) {
        std::string mode = race.getParticipants()[playerIndex].getStrategy().getModeName();
        std::cout << "Mode         : ";
        setColor(getModeColor(mode));
        std::cout << mode << "\n";
        resetColor();
    }
    else {
        std::cout << "Mode         : Unknown\n";
    }

    std::cout << "=====================================================================\n\n";
}

