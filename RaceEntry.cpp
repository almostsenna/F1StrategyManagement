#include "RaceEntry.h"

RaceEntry::RaceEntry()
    : driver(), car(), strategy(), currentLap(0), totalTime(0.0), position(0), inPit(false) {
}

RaceEntry::RaceEntry(const Driver& driver, const F1Car& car, const Strategy& strategy)
    : driver(driver), car(car), strategy(strategy), currentLap(0), totalTime(0.0), position(0), inPit(false) {
}

const Driver& RaceEntry::getDriver() const {
    return driver;
}

const F1Car& RaceEntry::getCar() const {
    return car;
}

F1Car& RaceEntry::getCarRef() {
    return car;
}

const Strategy& RaceEntry::getStrategy() const {
    return strategy;
}

Strategy& RaceEntry::getStrategyRef() {
    return strategy;
}

int RaceEntry::getCurrentLap() const {
    return currentLap;
}

double RaceEntry::getTotalTime() const {
    return totalTime;
}

int RaceEntry::getPosition() const {
    return position;
}

bool RaceEntry::isInPit() const {
    return inPit;
}

void RaceEntry::setPosition(int position) {
    this->position = position;
}

void RaceEntry::addLap() {
    currentLap++;
}

void RaceEntry::addTime(double lapTime) {
    totalTime += lapTime;
}

void RaceEntry::setPitState(bool state) {
    inPit = state;
}