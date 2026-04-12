#include "Driver.h"
#include "ColorUtils.h"
#include <iostream>
#include <iomanip>

// Конструктори
Driver::Driver() : name("Unknown"), skill(50), consistency(50), tyreManagement(50) {}

Driver::Driver(const std::string& name, int skill, int consistency, int tyreManagement)
    : name(name), skill(skill), consistency(consistency), tyreManagement(tyreManagement) {
}

// Геттери
std::string Driver::getName() const { return name; }
int Driver::getSkill() const { return skill; }
int Driver::getConsistency() const { return consistency; }
int Driver::getTyreManagement() const { return tyreManagement; }

// Логіка симуляції
double Driver::getPaceBonus() const {
    return skill * 0.01;
}

double Driver::getTyreWearModifier() const {
    return 1.0 - (tyreManagement * 0.003);
}

// --- МЕТОДИ ІНТЕРФЕЙСУ (КОЛЬОРОВІ) ---

// Вивід списку всіх водіїв (таблиця)
void Driver::showDriverList(const std::vector<Driver>& drivers) {
    setColor(CYAN);
    std::cout << "\n========================== DRIVER LIST ==========================\n";
    std::cout << std::left << std::setw(4) << "No"
        << std::setw(20) << "Driver"
        << "Tier\n";
    std::cout << "-----------------------------------------------------------------\n";
    resetColor();

    int i = 1;
    for (const auto& d : drivers) {
        std::cout << std::left << std::setw(4) << i++
            << std::setw(20) << d.getName();

        // Логіка кольору для Тіру залежно від скіла
        if (d.getSkill() >= 93) {
            setColor(GOLD);
            std::cout << "Elite\n";
        }
        else if (d.getSkill() >= 88) {
            setColor(YELLOW);
            std::cout << "Top Tier\n";
        }
        else if (d.getSkill() >= 82) {
            setColor(GREEN);
            std::cout << "Strong\n";
        }
        else {
            setColor(GRAY);
            std::cout << "Developing\n";
        }
        resetColor();
    }
    setColor(CYAN);
    std::cout << "=================================================================\n";
    resetColor();
}

// Вивід профілю конкретного водія
void Driver::displayProfile() const {
    setColor(YELLOW);
    std::cout << "\n======================== DRIVER PROFILE ========================\n";
    resetColor();

    std::cout << std::left << std::setw(18) << "Name" << ": " << name << "\n";
    std::cout << "----------------------------------------------------------------\n";

    // Характеристики
    setColor(CYAN);  std::cout << std::setw(18) << "Skill" << ": ";
    setColor(GREEN); std::cout << skill << "\n";

    setColor(CYAN);  std::cout << std::setw(18) << "Consistency" << ": ";
    setColor(GREEN); std::cout << consistency << "\n";

    setColor(CYAN);  std::cout << std::setw(18) << "Tyre Management" << ": ";
    setColor(GREEN); std::cout << tyreManagement << "\n";

    resetColor();
    std::cout << "----------------------------------------------------------------\n";

    setColor(YELLOW); std::cout << "Status" << ": ";
    resetColor();
    std::cout << "Active & Ready to Race\n";

    setColor(YELLOW);
    std::cout << "================================================================\n";
    resetColor();
}