#include "GameController.h"
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
    std::cout << "\n========================================\n";
    std::cout << " Formula 1 Race Strategy Simulator\n";
    std::cout << "========================================\n";
    std::cout << "1. Start New Race\n";
    std::cout << "2. Show Drivers\n";
    std::cout << "3. Show Driver Bio\n";
    std::cout << "4. Choose Race Type\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter choice: ";
}

Track GameController::chooseTrack() const {
    int choice = 0;
    std::cout << "Choose track:\n";
    std::cout << "1. Silverstone\n2. Monza\n3. Monaco\n4. Spa-Francorchamps\n";
    std::cout << "5. Suzuka\n6. Bahrain\n7. Imola\n8. Red Bull Ring\n";
    std::cout << "9. Singapore\n10. Interlagos\n";
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

std::string GameController::chooseDriverName() const {
    if (driverProfiles.empty()) {
        std::cout << "No drivers available. Verstappen selected by default.\n";
        return "Verstappen";
    }
    std::cout << "\nChoose your driver:\n";
    for (size_t i = 0; i < driverProfiles.size(); i++) {
        const auto& d = driverProfiles[i];
        std::cout << std::setw(2) << (i + 1) << ". "
            << std::setw(12) << std::left << d.name
            << " | Team: " << std::setw(15) << d.team
            << " | #" << d.number << "\n";
    }
    std::cout << "Enter choice: ";
    int choice = 0;
    std::cin >> choice;
    std::cin.ignore();
    if (choice < 1 || choice > static_cast<int>(driverProfiles.size())) {
        std::cout << "Invalid choice. Verstappen selected by default.\n";
        return "Verstappen";
    }
    return driverProfiles[choice - 1].name;
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
        if (participants[i].getDriver().getName() == playerDriverName)
            return static_cast<int>(i);
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
        break;
    case RaceType::Custom:
        modifiedTrack.setLaps(customLapCount);
        break;
    default:
        break;
    }
    return modifiedTrack;
}

void GameController::setupTestRace() {
    Track baseTrack = chooseTrack();
    Track selectedTrack = applyRaceTypeToTrack(baseTrack);
    playerDriverName = chooseDriverName();
    std::cout << "\nSelected track: " << selectedTrack.getName() << "\n";
    std::cout << "Laps: " << selectedTrack.getLaps() << "\n";
    std::cout << "Your driver: " << playerDriverName << "\n\n";
    setupFullGridRace(selectedTrack);
}

// *** НОВИЙ МЕТОД — вибір без cin ***
void GameController::setupRaceDirectly(int trackIndex, int driverIndex) {
    Track baseTrack;
    switch (trackIndex) {
    case 0:  baseTrack = createSilverstone();  break;
    case 1:  baseTrack = createMonza();        break;
    case 2:  baseTrack = createMonaco();       break;
    case 3:  baseTrack = createSpa();          break;
    case 4:  baseTrack = createSuzuka();       break;
    case 5:  baseTrack = createBahrain();      break;
    case 6:  baseTrack = createImola();        break;
    case 7:  baseTrack = createRedBullRing();  break;
    case 8:  baseTrack = createSingapore();    break;
    case 9:  baseTrack = createInterlagos();   break;
    default: baseTrack = createSilverstone();  break;
    }

    Track selectedTrack = applyRaceTypeToTrack(baseTrack);

    if (driverIndex >= 0 && driverIndex < (int)driverProfiles.size())
        playerDriverName = driverProfiles[driverIndex].name;
    else
        playerDriverName = "Verstappen";

    std::cout << "\nSelected track : " << selectedTrack.getName() << "\n";
    std::cout << "Your driver    : " << playerDriverName << "\n";
    std::cout << "Laps           : " << selectedTrack.getLaps() << "\n\n";

    setupFullGridRace(selectedTrack);
}

void GameController::start() {
    race.startRace();
}

void GameController::handlePlayerCommand() {
    int playerIndex = findPlayerIndex();
    const auto& participants = race.getParticipants();
    if (playerIndex < 0 || playerIndex >= static_cast<int>(participants.size()))
        return;

    std::cout << "\nYour driver: " << participants[playerIndex].getDriver().getName() << "\n";
    std::cout << "Choose action:\n";
    std::cout << "1. Push\n2. Normal\n3. Conserve\n";
    std::cout << "4. Pit for Soft\n5. Pit for Medium\n6. Pit for Hard\n7. Continue\n";
    std::cout << "Enter choice: ";

    int choice = 0;
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1: race.setParticipantMode(playerIndex, RaceMode::Push);    break;
    case 2: race.setParticipantMode(playerIndex, RaceMode::Normal);  break;
    case 3: race.setParticipantMode(playerIndex, RaceMode::Conserve); break;
    case 4: race.forcePitStop(playerIndex, TyreCompound::Soft);      break;
    case 5: race.forcePitStop(playerIndex, TyreCompound::Medium);    break;
    case 6: race.forcePitStop(playerIndex, TyreCompound::Hard);      break;
    default: break;
    }
}

void GameController::simulateOneLap() {
    handlePlayerCommand();
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
        << std::setw(20) << "Driver"
        << std::setw(10) << "Gap"
        << std::setw(10) << "Mode"
        << std::setw(10) << "Tyre"
        << std::setw(10) << "Wear%"
        << std::setw(10) << "TempC"
        << std::setw(10) << "Fuel"
        << std::setw(14) << "Event"
        << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < participants.size(); i++) {
        const auto& entry = participants[i];
        std::string driverName = entry.getDriver().getName();
        if (driverName == playerDriverName) driverName += " [YOU]";

        std::string gapText = "Leader";
        if (i != 0) {
            double gap = entry.getTotalTime() - leaderTime;
            std::ostringstream oss;
            oss << "+" << std::fixed << std::setprecision(2) << gap;
            gapText = oss.str();
        }

        std::cout << std::left
            << std::setw(4) << entry.getPosition()
            << std::setw(20) << driverName
            << std::setw(10) << gapText
            << std::setw(10) << entry.getStrategy().getModeName()
            << std::setw(10) << entry.getCar().getTyre().getCompoundName();
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
    driverProfiles.clear();
    driverProfiles.push_back({ "Verstappen","Red Bull",1,"Netherlands",28,11,
        "Multiple-time world champion known for elite pace and aggressive racecraft.",
        "RB","Honda RBPT",96,94,88,1 });
    driverProfiles.push_back({ "Leclerc","Ferrari",16,"Monaco",28,8,
        "Fast and precise Ferrari driver with excellent qualifying pace.",
        "Ferrari","Ferrari",93,90,85,2 });
    driverProfiles.push_back({ "Norris","McLaren",4,"United Kingdom",26,7,
        "Quick and consistent driver with strong race awareness.",
        "McLaren","Mercedes",91,89,87,3 });
    driverProfiles.push_back({ "Hamilton","Ferrari",44,"United Kingdom",41,19,
        "Legendary champion with elite consistency and tyre management.",
        "Ferrari","Ferrari",95,95,92,4 });
    driverProfiles.push_back({ "Russell","Mercedes",63,"United Kingdom",28,7,
        "Balanced driver with strong technical feedback and consistency.",
        "Mercedes","Mercedes",91,90,87,5 });
    driverProfiles.push_back({ "Piastri","McLaren",81,"Australia",25,3,
        "Calm and efficient racer with strong long-run pace.",
        "McLaren","Mercedes",89,87,86,6 });
    driverProfiles.push_back({ "Alonso","Aston Martin",14,"Spain",44,23,
        "Extremely experienced and tactical driver.",
        "Aston Martin","Honda",92,94,90,7 });
    driverProfiles.push_back({ "Antonelli","Mercedes",12,"Italy",20,1,
        "Highly rated young driver beginning his Mercedes career.",
        "Mercedes","Mercedes",87,82,81,8 });
    driverProfiles.push_back({ "Sainz","Williams",55,"Spain",31,11,
        "Intelligent and very consistent driver with solid tyre management.",
        "Williams","Mercedes",90,91,88,9 });
    driverProfiles.push_back({ "Gasly","Alpine",10,"France",29,9,
        "Quick and experienced driver with strong recovery pace.",
        "Alpine","Renault",88,87,85,10 });
    driverProfiles.push_back({ "Albon","Williams",23,"Thailand",29,7,
        "Strong driver known for maximizing difficult machinery.",
        "Williams","Mercedes",88,87,86,11 });
    driverProfiles.push_back({ "Perez","Cadillac",11,"Mexico",35,13,
        "Excellent tyre manager and dependable long-run racer.",
        "Cadillac","Cadillac PU",89,91,92,12 });
    driverProfiles.push_back({ "Bottas","Cadillac",77,"Finland",36,13,
        "Experienced driver with strong qualifying pace and technical feedback.",
        "Cadillac","Cadillac PU",88,90,89,13 });
    driverProfiles.push_back({ "Ocon","Haas",31,"France",29,9,
        "Consistent racer with strong defensive driving.",
        "Haas","Ferrari",87,88,86,14 });
    driverProfiles.push_back({ "Hulkenberg","Audi",27,"Germany",38,13,
        "Experienced and dependable driver with strong consistency.",
        "Audi","Audi",87,89,88,15 });
    driverProfiles.push_back({ "Stroll","Aston Martin",18,"Canada",27,9,
        "Reliable midfield-level driver with occasional strong weekends.",
        "Aston Martin","Honda",84,83,82,16 });
    driverProfiles.push_back({ "Lawson","VCARB",30,"New Zealand",24,2,
        "Aggressive and promising driver with solid race instincts.",
        "VCARB","Honda RBPT",84,82,81,17 });
    driverProfiles.push_back({ "Colapinto","Alpine",43,"Argentina",23,2,
        "Young, exciting driver with strong adaptability.",
        "Alpine","Renault",85,81,80,18 });
    driverProfiles.push_back({ "Bearman","Haas",87,"United Kingdom",21,1,
        "Young driver with aggressive style and high potential.",
        "Haas","Ferrari",84,79,78,19 });
    driverProfiles.push_back({ "Bortoleto","Audi",5,"Brazil",21,1,
        "Promising rookie stepping into Audi's new era.",
        "Audi","Audi",84,80,79,20 });
    driverProfiles.push_back({ "Tsunoda","Red Bull",22,"Japan",26,6,
        "Fast and improving driver with strong race pace.",
        "RB","Honda RBPT",88,85,84,21 });
    driverProfiles.push_back({ "Lindblad","VCARB",25,"United Kingdom",19,1,
        "Highly rated rookie entering Formula 1 with strong junior credentials.",
        "VCARB","Honda RBPT",83,78,77,22 });
}

void GameController::showDrivers() const {
    std::cout << "\n================================ DRIVER LIST ================================\n";
    std::cout << std::left
        << std::setw(4) << "No"
        << std::setw(15) << "Driver"
        << std::setw(15) << "Team"
        << std::setw(8) << "#"
        << std::setw(15) << "Nation"
        << std::setw(12) << "Tier"
        << "\n";
    std::cout << "-----------------------------------------------------------------------------\n";
    for (size_t i = 0; i < driverProfiles.size(); i++) {
        const auto& d = driverProfiles[i];
        std::cout << std::left
            << std::setw(4) << (i + 1)
            << std::setw(15) << d.name
            << std::setw(15) << d.team
            << std::setw(8) << d.number
            << std::setw(15) << d.nationality
            << std::setw(12) << getDriverTier(d)
            << "\n";
    }
    std::cout << "=============================================================================\n";
}

void GameController::showDriverBio() const {
    if (driverProfiles.empty()) {
        std::cout << "\nNo drivers available.\n";
        return;
    }
    std::cout << "\nChoose driver to view bio:\n";
    for (size_t i = 0; i < driverProfiles.size(); i++)
        std::cout << i + 1 << ". " << driverProfiles[i].name << "\n";

    std::cout << "Enter choice: ";
    int choice = 0;
    std::cin >> choice;
    std::cin.ignore();

    if (choice < 1 || choice > static_cast<int>(driverProfiles.size())) {
        std::cout << "Invalid choice.\n";
        return;
    }
    const auto& d = driverProfiles[choice - 1];
    std::cout << "\n============================== DRIVER PROFILE ==============================\n";
    std::cout << d.name << "  (#" << d.number << ")\n";
    std::cout << "---------------------------------------------------------------------------\n";
    std::cout << "Team           : " << d.team << "\n";
    std::cout << "Nationality    : " << d.nationality << "\n";
    std::cout << "Age            : " << d.age << "\n";
    std::cout << "Experience     : " << d.experienceYears << " years\n";
    std::cout << "Car            : " << d.carModel << "\n";
    std::cout << "Engine         : " << d.engineName << "\n";
    std::cout << "Tier           : " << getDriverTier(d) << "\n";
    std::cout << "---------------------------------------------------------------------------\n";
    std::cout << "Skill          : " << d.skill << "\n";
    std::cout << "Consistency    : " << d.consistency << "\n";
    std::cout << "Tyre Management: " << d.tyreManagement << "\n";
    std::cout << "---------------------------------------------------------------------------\n";
    std::cout << "Bio            : " << d.bio << "\n";
    std::cout << "===========================================================================\n";
}

void GameController::chooseRaceType() {
    int choice = 0;
    std::cout << "\nChoose race type:\n1. Sprint\n2. Grand Prix\n3. Custom\nEnter choice: ";
    std::cin >> choice;
    std::cin.ignore();
    switch (choice) {
    case 1:
        selectedRaceType = RaceType::Sprint;
        std::cout << "Sprint selected.\n";
        break;
    case 2:
        selectedRaceType = RaceType::GrandPrix;
        std::cout << "Grand Prix selected.\n";
        break;
    case 3:
        selectedRaceType = RaceType::Custom;
        std::cout << "Enter custom lap count: ";
        std::cin >> customLapCount;
        std::cin.ignore();
        if (customLapCount <= 0) {
            customLapCount = 10;
            std::cout << "Invalid. Default 10 applied.\n";
        }
        std::cout << "Custom race: " << customLapCount << " laps.\n";
        break;
    default:
        std::cout << "Invalid. Grand Prix remains selected.\n";
        selectedRaceType = RaceType::GrandPrix;
        break;
    }
}

void GameController::run() {
    bool running = true;
    while (running) {
        showMainMenu();
        int choice = 0;
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
        case 1:
            setupTestRace();
            start();
            while (!isRaceFinished()) {
                printStandings();
                simulateOneLap();
            }
            printStandings();
            std::cout << "\nRace finished!\n";
            break;
        case 2: showDrivers();    break;
        case 3: showDriverBio();  break;
        case 4: chooseRaceType(); break;
        case 5:
            running = false;
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid menu choice.\n";
            break;
        }
    }
}

Engine GameController::createEngineForTeam(const std::string& team) const {
    if (team == "Red Bull" || team == "VCARB")              return Engine("Honda RBPT", 950, 92);
    if (team == "Ferrari" || team == "Haas")               return Engine("Ferrari", 945, 90);
    if (team == "Mercedes" || team == "McLaren" || team == "Williams") return Engine("Mercedes", 940, 94);
    if (team == "Aston Martin")                             return Engine("Honda", 944, 91);
    if (team == "Alpine")                                   return Engine("Renault", 930, 88);
    if (team == "Audi")                                     return Engine("Audi", 936, 89);
    if (team == "Cadillac")                                 return Engine("Cadillac PU", 938, 90);
    return Engine("Generic Engine", 900, 85);
}

F1Car GameController::createCarForProfile(const DriverProfile& profile) const {
    Engine engine = createEngineForTeam(profile.team);
    TyreCompound startCompound = TyreCompound::Medium;
    if (profile.startingPosition <= 6)  startCompound = TyreCompound::Soft;
    else if (profile.startingPosition <= 14) startCompound = TyreCompound::Medium;
    else                                     startCompound = TyreCompound::Hard;
    return F1Car(profile.carModel, engine, Tyre(startCompound), 798.0, 100.0);
}

Strategy GameController::createStrategyForPosition(int startingPosition) const {
    if (startingPosition <= 4)  return Strategy(RaceMode::Push, 4, TyreCompound::Medium);
    else if (startingPosition <= 10) return Strategy(RaceMode::Normal, 5, TyreCompound::Hard);
    else if (startingPosition <= 16) return Strategy(RaceMode::Normal, 6, TyreCompound::Hard);
    else                             return Strategy(RaceMode::Conserve, 7, TyreCompound::Medium);
}

void GameController::setupFullGridRace(const Track& selectedTrack) {
    race = Race(selectedTrack);
    std::vector<DriverProfile> sortedProfiles = driverProfiles;
    std::sort(sortedProfiles.begin(), sortedProfiles.end(),
        [](const DriverProfile& a, const DriverProfile& b) {
            return a.startingPosition < b.startingPosition;
        });
    for (const auto& profile : sortedProfiles) {
        Driver driver(profile.name, profile.skill, profile.consistency, profile.tyreManagement);
        F1Car car = createCarForProfile(profile);
        Strategy strategy = createStrategyForPosition(profile.startingPosition);
        race.addParticipant(RaceEntry(driver, car, strategy));
    }
}