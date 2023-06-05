#include "ChargingStation.h"

ChargingStation::ChargingStation(unsigned int id, int x, int y, double onePercentChargingTime) : id(id), x(x), y(y), onePercentChargingTime(onePercentChargingTime) {}

unsigned int ChargingStation::getId() const {
    return id;
}

int ChargingStation::getX() const {
    return x;
}

int ChargingStation::getY() const {
    return y;
}

double ChargingStation::getOnePercentChargingTime() const {
    return onePercentChargingTime;
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
