#pragma once
#include <string>
#include <vector> // Додано для роботи зі списком водіїв

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

    // --- НОВІ МЕТОДИ ДЛЯ ІНТЕРФЕЙСУ ---

    // Статичний метод для виводу таблиці всіх водіїв (Скріншот №2)
    static void showDriverList(const std::vector<Driver>& drivers);

    // Метод для виводу профілю конкретного водія (Скріншот №4)
    void displayProfile() const;
};