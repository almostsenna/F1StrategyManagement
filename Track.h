#pragma once
#include <string>

class Track {
private:
    std::string name;
    double length;
    int laps;
    double tyreWearFactor;
    double baseLapTime;

public:
    Track();
    Track(const std::string& name, double length, int laps, double tyreWearFactor, double baseLapTime);

    std::string getName() const;
    double getLength() const;
    int getLaps() const;
    double getTyreWearFactor() const;
    double getBaseLapTime() const;
};