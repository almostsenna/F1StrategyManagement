#pragma once
#include <string>

class Engine {
private:
    std::string name;
    int power;
    int reliability;

public:
    Engine();
    Engine(const std::string& name, int power, int reliability);

    std::string getName() const;
    int getPower() const;
    int getReliability() const;

    double getPowerBonus() const;
};