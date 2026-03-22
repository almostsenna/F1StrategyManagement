#include "Strategy.h"

Strategy::Strategy() : mode(RaceMode::Normal), plannedPitLap(5) {}

Strategy::Strategy(RaceMode mode, int plannedPitLap)
    : mode(mode), plannedPitLap(plannedPitLap) {
}

RaceMode Strategy::getMode() const {
    return mode;
}

int Strategy::getPlannedPitLap() const {
    return plannedPitLap;
}

void Strategy::setMode(RaceMode mode) {
    this->mode = mode;
}

bool Strategy::shouldPit(int currentLap, double tyreWear) const {
    return currentLap == plannedPitLap || tyreWear >= 70.0;
}

double Strategy::getPaceModifier() const {
    switch (mode) {
    case RaceMode::Push: return -0.8;
    case RaceMode::Normal: return 0.0;
    case RaceMode::Conserve: return 0.6;
    default: return 0.0;
    }
}

double Strategy::getWearModifier() const {
    switch (mode) {
    case RaceMode::Push: return 1.35;
    case RaceMode::Normal: return 1.0;
    case RaceMode::Conserve: return 0.75;
    default: return 1.0;
    }
}