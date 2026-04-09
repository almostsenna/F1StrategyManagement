#pragma once
#include <string>
#include "Driver.h"
#include "F1Car.h"
#include "Strategy.h"

class RaceEntry {
private:
    Driver driver;
    F1Car car;
    Strategy strategy;
    int currentLap;
    double totalTime;
    int position;
    bool inPit;
    std::string lastEvent;

public:
    RaceEntry();
    RaceEntry(const Driver& driver, const F1Car& car, const Strategy& strategy);

    const Driver& getDriver() const;
    const F1Car& getCar() const;
    F1Car& getCarRef();
    const Strategy& getStrategy() const;
    Strategy& getStrategyRef();

    int getCurrentLap() const;
    double getTotalTime() const;
    int getPosition() const;
    bool isInPit() const;
    std::string getLastEvent() const;

    void setPosition(int position);
    void addLap();
    void addTime(double lapTime);
    void setPitState(bool state);

    void setLastEvent(const std::string& event);
    void clearLastEvent();
};