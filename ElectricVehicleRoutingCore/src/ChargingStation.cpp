#include "ChargingStation.h"

ChargingStation::ChargingStation(unsigned int id, int x, int y) : id(id), x(x), y(y) {}

unsigned int ChargingStation::getId() const {
    return id;
}

int ChargingStation::getX() const {
    return x;
}

int ChargingStation::getY() const {
    return y;
}

double ChargingStation::getChargingTime(double currentBatteryPercentage, double finalBatteryPercentage, double vehicleTime) {
    double chargingTime = 0;
    for (auto& charging : onePercentChargingTimes) {
        if (finalBatteryPercentage >= charging.highLimit) {
            if (currentBatteryPercentage >= charging.lowLimit && currentBatteryPercentage <= charging.highLimit) {
                chargingTime += (charging.highLimit - currentBatteryPercentage) * std::max(charging.onePercentChargingTime, vehicleTime);
            }
            else if (currentBatteryPercentage < charging.lowLimit) {
                chargingTime += (charging.highLimit - charging.lowLimit) * std::max(charging.onePercentChargingTime, vehicleTime);
            }
        }
    }

    return chargingTime;
}

const std::vector<ChargingTime> &ChargingStation::getChargingTimes() const
{
    return onePercentChargingTimes;
}

const std::vector<ChargerType> &ChargingStation::getChargerTypes() const {
    return chargerTypes;
}

bool ChargingStation::operator==(const ChargingStation &rhs) const {
    return id == rhs.id;
}

bool ChargingStation::operator!=(const ChargingStation &rhs) const {
    return !(rhs == *this);
}

bool ChargingStation::isCompatibleWith(const ElectricVehicle& electricVehicle) {
    if(std::count(chargerTypes.begin(), chargerTypes.end(), electricVehicle.getChargerType()))
        return true;
    return false;
}

void ChargingStation::addChargerType(ChargerType chargerType) {
    chargerTypes.push_back(chargerType);
}

void ChargingStation::addChargingTime(ChargingTime chargingTime)
{
    onePercentChargingTimes.push_back(chargingTime);
}
