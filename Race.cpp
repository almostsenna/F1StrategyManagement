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

    // Engine effect depends on track power sensitivity
    lapTime -= car.getEngine().getPowerBonus() * track.getPowerSensitivity();

    // Driver effect depends on track technicality
    lapTime -= driver.getPaceBonus() * track.getTechnicality();

    // Tyre grip bonus
    lapTime -= car.getTyre().getGripBonus();

    // Extra wear penalty
    lapTime += car.getTyre().getWear() * 0.03;

    // Fuel penalty
    lapTime += car.getFuelPenalty();

    // Strategy mode
    lapTime += strategy.getPaceModifier();

    // Random variation
    int randomValue = std::rand() % 100;
    double randomFactor = (randomValue / 100.0) - 0.5;
    lapTime += randomFactor;

    // Tyre wear update
    double wearAmount = track.getTyreWearFactor()
        * strategy.getWearModifier()
        * driver.getTyreWearModifier();

    car.getTyreRef().increaseWear(wearAmount);

    // Tyre temperature update
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

    // Fuel burn
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