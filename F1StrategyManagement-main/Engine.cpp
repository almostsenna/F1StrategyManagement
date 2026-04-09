#include "Engine.h"

Engine::Engine() : name("Generic Engine"), power(900), reliability(90) {}

Engine::Engine(const std::string& name, int power, int reliability)
    : name(name), power(power), reliability(reliability) {
}

std::string Engine::getName() const {
    return name;
}

int Engine::getPower() const {
    return power;
}

int Engine::getReliability() const {
    return reliability;
}

double Engine::getPowerBonus() const {
    return (power - 850) * 0.01;
}