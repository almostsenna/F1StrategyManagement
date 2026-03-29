#pragma once
#include <string>
#include "Tyre.h"

enum class RaceMode {
    Push,
    Normal,
    Conserve
};

class Strategy {
private:
    RaceMode mode;
    int plannedPitLap;
    TyreCompound nextPitCompound;

public:
    Strategy();
    Strategy(RaceMode mode, int plannedPitLap, TyreCompound nextPitCompound);

    RaceMode getMode() const;
    int getPlannedPitLap() const;
    TyreCompound getNextPitCompound() const;

    void setMode(RaceMode mode);
    void setNextPitCompound(TyreCompound compound);

    bool shouldPit(int currentLap, double tyreWear) const;

    double getPaceModifier() const;
    double getWearModifier() const;
    std::string getModeName() const;
};