#include "Race.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

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

    lapTime -= driver.getPaceBonus();
    lapTime -= car.getEngine().getPowerBonus();
    lapTime -= car.getTyre().getGripBonus();
    lapTime += car.getFuelPenalty();
    lapTime += strategy.getPaceModifier();

    int randomValue = std::rand() % 100;
    double randomFactor = (randomValue / 100.0) - 0.5;
    lapTime += randomFactor;

    double wearAmount = track.getTyreWearFactor() * strategy.getWearModifier() * driver.getTyreWearModifier();
    car.getTyreRef().increaseWear(wearAmount);

    if (strategy.getMode() == RaceMode::Push) {
        car.getTyreRef().changeTemperature(3.0);
    }
    else if (strategy.getMode() == RaceMode::Conserve) {
        car.getTyreRef().changeTemperature(-2.0);
    }
    else {
        car.getTyreRef().changeTemperature(1.0);
    }

    car.burnFuel(2.2);

    return lapTime;
}

void Race::processPitStop(RaceEntry& entry) {
    entry.setPitState(true);
    entry.addTime(22.0);

    TyreCompound nextCompound = TyreCompound::Hard;

    if (entry.getCar().getTyre().getCompound() == TyreCompound::Soft) {
        nextCompound = TyreCompound::Medium;
    }
    else if (entry.getCar().getTyre().getCompound() == TyreCompound::Medium) {
        nextCompound = TyreCompound::Hard;
    }

    entry.getCarRef().changeTyres(nextCompound);
    entry.setPitState(false);
}

void Race::simulateLap() {
    if (finished) return;

    currentLap++;

    for (auto& entry : participants) {
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

bool Race::isFinished() const {
    return finished;
}

int Race::getCurrentLap() const {
    return currentLap;
}

const Track& Race::getTrack() const {
    return track;
}

const std::vector<RaceEntry>& Race::getParticipants() const {
    return participants;
}