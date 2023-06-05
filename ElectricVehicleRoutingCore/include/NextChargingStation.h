#pragma once

#include "ChargingStation.h"

class NextChargingStation {
public:
    NextChargingStation(ChargingStation chargingStation, double distance, unsigned int avgSpeed,
                        double time);

    static NextChargingStation createFromCoordinates(ChargingStation chargingStation, unsigned int avgSpeed, int x, int y);

    bool operator<(const NextChargingStation &rhs) const;

    bool operator>(const NextChargingStation &rhs) const;

    bool operator<=(const NextChargingStation &rhs) const;

    bool operator>=(const NextChargingStation &rhs) const;

    ChargingStation getChargingStation() const;

    double getDistance() const;

    unsigned int getAvgSpeed() const;

    double getTime() const;

private:
    ChargingStation chargingStation;
    double distance;
    unsigned int avgSpeed;
    double time;

    static double euclidean_distance(int x, int y, unsigned int x1, unsigned int y1);
    static double fRand(double fMin, double fMax);
};
