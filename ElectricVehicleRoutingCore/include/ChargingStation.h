#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>
#include "ChargerType.h"
#include "ElectricVehicle.h"

class ChargingStation {
public:
    ChargingStation(unsigned int id, int x, int y, double onePercentChargingTime);

    ChargingStation() = default;

    unsigned int getId() const;

    int getX() const;

    int getY() const;

    double getOnePercentChargingTime() const;

    const std::vector<ChargerType> &getChargerTypes() const;

    bool isCompatibleWith(const ElectricVehicle& electricVehicle);

    void addChargerType(ChargerType chargerType);

    bool operator==(const ChargingStation &rhs) const;

    bool operator!=(const ChargingStation &rhs) const;

private:
    unsigned int id;
    int x;
    int y;
    double onePercentChargingTime;
    std::vector<ChargerType> chargerTypes;
};
