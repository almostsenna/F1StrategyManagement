#pragma once
#include <string>
#include "Engine.h"
#include "Tyre.h"

class F1Car {
private:
    std::string model;
    Engine engine;
    Tyre tyre;
    double weight;
    double fuel;

public:
    F1Car();
    F1Car(const std::string& model, const Engine& engine, const Tyre& tyre, double weight, double fuel);

    std::string getModel() const;
    Engine getEngine() const;
    const Tyre& getTyre() const;
    Tyre& getTyreRef();

    double getWeight() const;
    double getFuel() const;
    double getCurrentWeight() const;

    void burnFuel(double amount);
    void changeTyres(TyreCompound compound);

    double getFuelPenalty() const;
};