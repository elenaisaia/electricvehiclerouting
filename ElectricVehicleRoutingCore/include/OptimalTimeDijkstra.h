#pragma once

#include <queue>
#include "DirectedGraphForChargingStations.h"
#include "ElectricVehicle.h"

struct IdPair {
    unsigned int id, maxBatteryPercentage;

    bool operator==(const IdPair& rhs) const {
        if (id == rhs.id && maxBatteryPercentage == rhs.maxBatteryPercentage)
            return true;
        return false;
    }

    bool operator!=(const IdPair& rhs) const {
        return !(rhs == *this);
    }
};

namespace std {
    template<>
    struct hash<IdPair> {
        auto operator()(const IdPair& idPair) const -> size_t {
            return hash<string>()("" + idPair.id + idPair.maxBatteryPercentage);
        }
    };
}

class OptimalTimeDijkstra {
public:
    OptimalTimeDijkstra(ElectricVehicle &vehicle, DirectedGraphForChargingStations &graph, unsigned int sourceId, unsigned int destinationId);

    double findCost();

private:
    ElectricVehicle &vehicle;
    DirectedGraphForChargingStations &graph;
    unsigned int sourceId;
    unsigned int destinationId;
    std::priority_queue<NextChargingStation> queue;
    std::unordered_map<IdPair, double> cost;
    std::unordered_map<IdPair, IdPair> parent;
    std::unordered_map<IdPair, bool> visited;
};
