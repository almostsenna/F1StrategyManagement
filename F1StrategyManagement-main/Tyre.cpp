#include "Tyre.h"
#include <algorithm>

Tyre::Tyre() : compound(TyreCompound::Medium), wear(0.0), temperature(90.0) {}

Tyre::Tyre(TyreCompound compound) : compound(compound), wear(0.0), temperature(90.0) {}

TyreCompound Tyre::getCompound() const {
    return compound;
}

double Tyre::getWear() const {
    return wear;
}

double Tyre::getTemperature() const {
    return temperature;
}

void Tyre::increaseWear(double amount) {
    wear += amount;
    if (wear > 100.0) wear = 100.0;
}

void Tyre::changeTemperature(double amount) {
    temperature += amount;
    temperature = std::clamp(temperature, 60.0, 140.0);
}

void Tyre::reset(TyreCompound newCompound) {
    compound = newCompound;
    wear = 0.0;
    temperature = 90.0;
}

double Tyre::getGripBonus() const {
    double baseGrip = 0.0;

    switch (compound) {
    case TyreCompound::Soft:   baseGrip = 1.4; break;
    case TyreCompound::Medium: baseGrip = 1.0; break;
    case TyreCompound::Hard:   baseGrip = 0.6; break;
    }

    double wearPenalty = wear * 0.02;
    double tempPenalty = 0.0;

    if (temperature < 80.0) tempPenalty += 0.3;
    if (temperature > 110.0) tempPenalty += 0.5;

    return baseGrip - wearPenalty - tempPenalty;
}

std::string Tyre::getCompoundName() const {
    switch (compound) {
    case TyreCompound::Soft: return "Soft";
    case TyreCompound::Medium: return "Medium";
    case TyreCompound::Hard: return "Hard";
    default: return "Unknown";
    }
}