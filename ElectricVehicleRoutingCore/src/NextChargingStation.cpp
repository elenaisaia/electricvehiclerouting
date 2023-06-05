#include <cmath>
#include "NextChargingStation.h"

NextChargingStation::NextChargingStation(ChargingStation chargingStation, double distance,
                                         unsigned int avgSpeed, double time) : chargingStation(chargingStation),
                                                                                     distance(distance),
                                                                                     avgSpeed(avgSpeed), time(time) {}

NextChargingStation NextChargingStation::createFromCoordinates(ChargingStation chargingStation, unsigned int avgSpeed, int x, int y) {
    double distance = euclidean_distance(x, y, chargingStation.getX(), chargingStation.getY()) * fRand(1, sqrt(2));
    double time = distance / avgSpeed;
    return NextChargingStation{chargingStation, distance, avgSpeed, time};
}

double NextChargingStation::euclidean_distance(int x, int y, unsigned int x1, unsigned int y1) {
    return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
}

double NextChargingStation::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

bool NextChargingStation::operator<(const NextChargingStation &rhs) const {
    if (chargingStation.getOnePercentChargingTime() + time <
            rhs.chargingStation.getOnePercentChargingTime() + rhs.getTime())
        return true;
    if (rhs.chargingStation.getOnePercentChargingTime() + rhs.getTime() <
            chargingStation.getOnePercentChargingTime() + time )
        return false;
    if (time < rhs.getTime())
        return true;
    if (rhs.getTime() < time)
        return false;
    if (chargingStation.getOnePercentChargingTime() < rhs.chargingStation.getOnePercentChargingTime())
        return true;
    if (rhs.chargingStation.getOnePercentChargingTime() < chargingStation.getOnePercentChargingTime())
        return false;
    return distance < rhs.getDistance();
}

bool NextChargingStation::operator>(const NextChargingStation &rhs) const {
    return rhs < *this;
}

bool NextChargingStation::operator<=(const NextChargingStation &rhs) const {
    return !(rhs < *this);
}

bool NextChargingStation::operator>=(const NextChargingStation &rhs) const {
    return !(*this < rhs);
}

ChargingStation NextChargingStation::getChargingStation() const {
    return chargingStation;
}

double NextChargingStation::getDistance() const {
    return distance;
}

unsigned int NextChargingStation::getAvgSpeed() const {
    return avgSpeed;
}

double NextChargingStation::getTime() const {
    return time;
}
