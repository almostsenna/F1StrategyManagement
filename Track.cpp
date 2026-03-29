#include "Track.h"

Track::Track()
    : name("Generic Track"),
    length(5.0),
    laps(10),
    tyreWearFactor(1.0),
    baseLapTime(90.0),
    powerSensitivity(1.0),
    technicality(1.0),
    trackTemperature(30.0) {
}

Track::Track(const std::string& name,
    double length,
    int laps,
    double tyreWearFactor,
    double baseLapTime,
    double powerSensitivity,
    double technicality,
    double trackTemperature)
    : name(name),
    length(length),
    laps(laps),
    tyreWearFactor(tyreWearFactor),
    baseLapTime(baseLapTime),
    powerSensitivity(powerSensitivity),
    technicality(technicality),
    trackTemperature(trackTemperature) {
}

std::string Track::getName() const {
    return name;
}

double Track::getLength() const {
    return length;
}

int Track::getLaps() const {
    return laps;
}

double Track::getTyreWearFactor() const {
    return tyreWearFactor;
}

double Track::getBaseLapTime() const {
    return baseLapTime;
}

double Track::getPowerSensitivity() const {
    return powerSensitivity;
}

double Track::getTechnicality() const {
    return technicality;
}

double Track::getTrackTemperature() const {
    return trackTemperature;
}