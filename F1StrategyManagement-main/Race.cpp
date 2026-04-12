#include "Race.h"
#include "ColorUtils.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

Race::Race() : track(), currentLap(0), finished(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Race::Race(const Track& track) : track(track), currentLap(0), finished(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Race::addParticipant(const RaceEntry& entry) {
    participants.push_back(entry);
}

void Race::startRace() {
    currentLap = 0;
    finished = false;
    updatePositions();
}

double Race::calculateLapTime(RaceEntry& entry) {
    const Driver& driver = entry.getDriver();
    F1Car& car = entry.getCarRef();
    Strategy& strategy = entry.getStrategyRef();

    double lapTime = track.getBaseLapTime();
    lapTime -= car.getEngine().getPowerBonus() * track.getPowerSensitivity();
    lapTime -= driver.getPaceBonus() * track.getTechnicality();
    lapTime -= car.getTyre().getGripBonus();
    lapTime += car.getTyre().getWear() * 0.03;
    lapTime += car.getFuelPenalty();
    lapTime += strategy.getPaceModifier();

    int randomValue = std::rand() % 100;
    double randomFactor = (randomValue / 100.0) - 0.5;
    lapTime += randomFactor;

    double wearAmount = track.getTyreWearFactor()
        * strategy.getWearModifier()
        * driver.getTyreWearModifier();
    car.getTyreRef().increaseWear(wearAmount);

    double baseTempEffect = (track.getTrackTemperature() - 30.0) * 0.1;

    if (strategy.getMode() == RaceMode::Push) {
        car.getTyreRef().changeTemperature(3.0 + baseTempEffect);
    }
    else if (strategy.getMode() == RaceMode::Conserve) {
        car.getTyreRef().changeTemperature(-2.0 + baseTempEffect);
    }
    else {
        car.getTyreRef().changeTemperature(1.0 + baseTempEffect);
    }

    car.burnFuel(2.2);
    return lapTime;
}


void Race::processPitStop(RaceEntry& entry) {
    entry.setPitState(true);

    TyreCompound nextCompound = entry.getStrategy().getNextPitCompound();
    std::string compoundName = Tyre(nextCompound).getCompoundName();

    entry.addTime(22.0);
    entry.setLastEvent("PIT -> " + compoundName);

    entry.getCarRef().changeTyres(nextCompound);
    entry.getStrategyRef().clearPitRequest();

    entry.setPitState(false);
}

void Race::simulateLap() {
    if (finished) return;

    currentLap++;

    for (auto& entry : participants) {
        entry.clearLastEvent();
        double lapTime = calculateLapTime(entry);
        entry.addTime(lapTime);
        entry.addLap();

        if (entry.getStrategy().shouldPit(currentLap, entry.getCar().getTyre().getWear())) {
            processPitStop(entry);
        }
    }

    updatePositions();

    if (currentLap >= track.getLaps()) {
        finishRace();
    }
}

void Race::updatePositions() {
    std::sort(participants.begin(), participants.end(),
        [](const RaceEntry& a, const RaceEntry& b) {
            return a.getTotalTime() < b.getTotalTime();
        });

    for (size_t i = 0; i < participants.size(); i++) {
        participants[i].setPosition(static_cast<int>(i + 1));
    }
}

void Race::finishRace() {
    finished = true;
}

void Race::setParticipantMode(int index, RaceMode mode) {
    if (index >= 0 && index < static_cast<int>(participants.size())) {
        participants[index].getStrategyRef().setMode(mode);
    }
}

void Race::forcePitStop(int index, TyreCompound compound) {
    if (index >= 0 && index < static_cast<int>(participants.size())) {
        participants[index].getStrategyRef().setNextPitCompound(compound);
        participants[index].getStrategyRef().requestPitStop();
    }
}

bool Race::isFinished() const { return finished; }
int Race::getCurrentLap() const { return currentLap; }
const Track& Race::getTrack() const { return track; }
const std::vector<RaceEntry>& Race::getParticipants() const { return participants; }

void Race::displayStatus() const {
    setColor(YELLOW);
    std::cout << "\n================================================================================\n";
    std::cout << " Lap " << currentLap << " / " << track.getLaps()
        << " | Track: " << track.getName() << "\n";
    std::cout << "================================================================================\n";

    setColor(CYAN);
    printf("%-4s %-18s %-10s %-10s %-8s %-7s %-7s %-7s %s\n",
        "Pos", "Driver", "Gap", "Mode", "Tyre", "Wear%", "TempC", "Fuel", "Event");
    resetColor();
    std::cout << "--------------------------------------------------------------------------------\n";

    double leaderTime = participants.empty() ? 0.0 : participants[0].getTotalTime();

    for (const auto& entry : participants) {
        bool isPlayer = (entry.getDriver().getName() == "Verstappen");

        if (isPlayer) setColor(BLUE);
        std::string label = entry.getDriver().getName() + (isPlayer ? " [YOU]" : "");
        printf("%-4d %-18s ", entry.getPosition(), label.c_str());
        resetColor();

        if (entry.getPosition() == 1) {
            printf("%-10s ", "Leader");
        }
        else {
            char gap[16];
            std::snprintf(gap, sizeof(gap), "+%.2f", entry.getTotalTime() - leaderTime);
            printf("%-10s ", gap);
        }

        RaceMode m = entry.getStrategy().getMode();
        if (m == RaceMode::Push)          setColor(RED);
        else if (m == RaceMode::Conserve) setColor(GREEN);
        printf("%-10s ", m == RaceMode::Push ? "Push" :
            (m == RaceMode::Conserve ? "Conserve" : "Normal"));
        resetColor();

        TyreCompound tc = entry.getCar().getTyre().getCompound();
        if (tc == TyreCompound::Soft)        setColor(RED);
        else if (tc == TyreCompound::Medium) setColor(YELLOW);
        else                                 setColor(WHITE);
        printf("%-8s ", entry.getCar().getTyre().getCompoundName().c_str());
        resetColor();

        printf("%-7.2f %-7.2f %-7.2f ",
            entry.getCar().getTyre().getWear(),
            entry.getCar().getTyre().getTemperature(),
            entry.getCar().getFuel());

        if (!entry.getLastEvent().empty()) {
            setColor(CYAN);
            printf("%s", entry.getLastEvent().c_str());
            resetColor();
        }

        printf("\n");
    }
    std::cout << "--------------------------------------------------------------------------------\n";
}