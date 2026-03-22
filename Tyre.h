#pragma once
#include <string>

enum class TyreCompound {
    Soft,
    Medium,
    Hard
};

class Tyre {
private:
    TyreCompound compound;
    double wear;
    double temperature;

public:
    Tyre();
    Tyre(TyreCompound compound);

    TyreCompound getCompound() const;
    double getWear() const;
    double getTemperature() const;

    void increaseWear(double amount);
    void changeTemperature(double amount);
    void reset(TyreCompound newCompound);

    double getGripBonus() const;
    std::string getCompoundName() const;
};