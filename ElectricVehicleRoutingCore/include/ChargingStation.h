#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>
#include "ChargerType.h"
#include "ElectricVehicle.h"

struct ChargingTime {
    unsigned int lowLimit, highLimit;
    double onePercentChargingTime;
};

class ChargingStation {
public:
    ChargingStation(unsigned int id, int x, int y);

    ChargingStation() = default;

    unsigned int getId() const;

    int getX() const;

    int getY() const;

    double getChargingTime(double currentBatteryPercentage, double finalBatteryPercentage, double vehicleTime);

    const std::vector<ChargingTime> &getChargingTimes() const;

    const std::vector<ChargerType> &getChargerTypes() const;

    bool isCompatibleWith(const ElectricVehicle& electricVehicle);

    void addChargerType(ChargerType chargerType);

    void addChargingTime(ChargingTime chargingTime);

    bool operator==(const ChargingStation &rhs) const;

    bool operator!=(const ChargingStation &rhs) const;

private:
    unsigned int id;
    int x;
    int y;
    std::vector<ChargingTime> onePercentChargingTimes;
    std::vector<ChargerType> chargerTypes;
};
