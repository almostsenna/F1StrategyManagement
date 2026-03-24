#pragma once
#include <string>

enum class RaceMode {
    Push,
    Normal,
    Conserve
};

class Strategy {
private:
    RaceMode mode;
    int plannedPitLap;

public:
    Strategy();
    Strategy(RaceMode mode, int plannedPitLap);

    RaceMode getMode() const;
    int getPlannedPitLap() const;

    void setMode(RaceMode mode);
    bool shouldPit(int currentLap, double tyreWear) const;

    double getPaceModifier() const;
    double getWearModifier() const;
    std::string getModeName() const;
};