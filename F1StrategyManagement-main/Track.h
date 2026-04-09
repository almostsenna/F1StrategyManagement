#pragma once
#include <string>

class Track {
private:
    std::string name;
    double length;
    int laps;
    double tyreWearFactor;
    double baseLapTime;
    double powerSensitivity;
    double technicality;
    double trackTemperature;

public:
    Track();
    Track(const std::string& name,
        double length,
        int laps,
        double tyreWearFactor,
        double baseLapTime,
        double powerSensitivity,
        double technicality,
        double trackTemperature);

    std::string getName() const;
    double getLength() const;
    int getLaps() const;
    double getTyreWearFactor() const;
    double getBaseLapTime() const;
    double getPowerSensitivity() const;
    double getTechnicality() const;
    double getTrackTemperature() const;
    void setLaps(int laps);

};