#include "Strategy.h"

Strategy::Strategy()
    : mode(RaceMode::Normal),
    plannedPitLap(5),
    nextPitCompound(TyreCompound::Hard),
    forcePitRequest(false) {
}

Strategy::Strategy(RaceMode mode, int plannedPitLap, TyreCompound nextPitCompound)
    : mode(mode),
    plannedPitLap(plannedPitLap),
    nextPitCompound(nextPitCompound),
    forcePitRequest(false) {
}

RaceMode Strategy::getMode() const {
    return mode;
}

int Strategy::getPlannedPitLap() const {
    return plannedPitLap;
}

TyreCompound Strategy::getNextPitCompound() const {
    return nextPitCompound;
}

bool Strategy::hasForcedPitRequest() const {
    return forcePitRequest;
}

void Strategy::setMode(RaceMode mode) {
    this->mode = mode;
}

void Strategy::setNextPitCompound(TyreCompound compound) {
    nextPitCompound = compound;
}

void Strategy::requestPitStop() {
    forcePitRequest = true;
}

void Strategy::clearPitRequest() {
    forcePitRequest = false;
}

bool Strategy::shouldPit(int currentLap, double tyreWear) const {
    return forcePitRequest || currentLap == plannedPitLap || tyreWear >= 70.0;
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

std::string Strategy::getModeName() const {
    switch (mode) {
    case RaceMode::Push: return "Push";
    case RaceMode::Normal: return "Normal";
    case RaceMode::Conserve: return "Conserve";
    default: return "Unknown";
    }
}