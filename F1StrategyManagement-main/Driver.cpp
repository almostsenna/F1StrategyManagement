#include "Driver.h"

Driver::Driver() : name("Unknown"), skill(50), consistency(50), tyreManagement(50) {}

Driver::Driver(const std::string& name, int skill, int consistency, int tyreManagement)
    : name(name), skill(skill), consistency(consistency), tyreManagement(tyreManagement) {
}

std::string Driver::getName() const {
    return name;
}

int Driver::getSkill() const {
    return skill;
}

int Driver::getConsistency() const {
    return consistency;
}

int Driver::getTyreManagement() const {
    return tyreManagement;
}

double Driver::getPaceBonus() const {
    return skill * 0.01;
}

double Driver::getTyreWearModifier() const {
    return 1.0 - (tyreManagement * 0.003);
}