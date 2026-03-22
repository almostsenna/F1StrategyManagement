#pragma once
#include <string>

class Driver {
private:
    std::string name;
    int skill;
    int consistency;
    int tyreManagement;

public:
    Driver();
    Driver(const std::string& name, int skill, int consistency, int tyreManagement);

    std::string getName() const;
    int getSkill() const;
    int getConsistency() const;
    int getTyreManagement() const;

    double getPaceBonus() const;
    double getTyreWearModifier() const;
};