#pragma once
#include <vector>
#include "Track.h"
#include "RaceEntry.h"

class Race {
private:
    Track track;
    std::vector<RaceEntry> participants;
    int currentLap;
    bool finished;

    double calculateLapTime(RaceEntry& entry);
    void processPitStop(RaceEntry& entry);

public:
    Race();
    Race(const Track& track);

    void addParticipant(const RaceEntry& entry);
    void startRace();
    void simulateLap();
    void updatePositions();
    void finishRace();


    void setParticipantMode(int index, RaceMode mode);
    void forcePitStop(int index, TyreCompound compound);
    bool isFinished() const;
    int getCurrentLap() const;
    const Track& getTrack() const;
    const std::vector<RaceEntry>& getParticipants() const;
};