#include "F1Car.h"

F1Car::F1Car()
    : model("Generic Car"), engine(), tyre(), weight(798.0), fuel(100.0) {
}

F1Car::F1Car(const std::string& model, const Engine& engine, const Tyre& tyre, double weight, double fuel)
    : model(model), engine(engine), tyre(tyre), weight(weight), fuel(fuel) {
}

std::string F1Car::getModel() const {
    return model;
}

Engine F1Car::getEngine() const {
    return engine;
}

const Tyre& F1Car::getTyre() const {
    return tyre;
}

Tyre& F1Car::getTyreRef() {
    return tyre;
}

double F1Car::getWeight() const {
    return weight;
}

double F1Car::getFuel() const {
    return fuel;
}

double F1Car::getCurrentWeight() const {
    return weight + fuel;
}

void F1Car::burnFuel(double amount) {
    fuel -= amount;
    if (fuel < 0.0) fuel = 0.0;
}

void F1Car::changeTyres(TyreCompound compound) {
    tyre.reset(compound);
}

double F1Car::getFuelPenalty() const {
    return fuel * 0.015;
}