#include "Track.h"

Track::Track()
    : name("Generic Track"), length(5.0), laps(10), tyreWearFactor(1.0), baseLapTime(90.0) {
}

Track::Track(const std::string& name, double length, int laps, double tyreWearFactor, double baseLapTime)
    : name(name), length(length), laps(laps), tyreWearFactor(tyreWearFactor), baseLapTime(baseLapTime) {
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