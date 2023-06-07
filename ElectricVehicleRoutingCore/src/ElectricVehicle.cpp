#include "ElectricVehicle.h"

ElectricVehicle::ElectricVehicle(unsigned int id, ChargerType chargerType, unsigned int batteryPercentage, double onePercentChargingTime) : id(id), chargerType(chargerType), batteryPercentage(batteryPercentage), onePercentChargingTime(onePercentChargingTime) {}

unsigned int ElectricVehicle::getId() const {
    return id;
}

ChargerType ElectricVehicle::getChargerType() const {
    return chargerType;
}

unsigned int ElectricVehicle::getBatteryPercentage() const {
    return batteryPercentage;
}

void ElectricVehicle::setBatteryPercentage(unsigned int batteryPercentage) {
    ElectricVehicle::batteryPercentage = batteryPercentage;
}

double ElectricVehicle::getOnePercentChargingTime() const {
    return onePercentChargingTime;
}

void ElectricVehicle::addCost(unsigned int minSpeed, unsigned int maxSpeed, double costPerTimeUnit) {
    SpeedCost cost{minSpeed, maxSpeed, costPerTimeUnit};
    ElectricVehicle::costs.push_back(cost);
}

double ElectricVehicle::getCostPerTimeUnit(unsigned int speed) {
    for(auto cost : costs) {
        if(speed >= cost.minSpeed && speed <= cost.maxSpeed)
            return cost.costPerTimeUnit;
    }
    return 0;
}
