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
        auto operator()(const IdPair& p) const -> size_t {
            uintmax_t hash = std::hash<unsigned int>{}(p.id);
            hash <<= sizeof(uintmax_t) * 4;
            hash ^= std::hash<unsigned int>{}(p.maxBatteryPercentage);
            return std::hash<uintmax_t>{}(hash);
        }
    };
}

class OptimalTimeDijkstra {
public:
    OptimalTimeDijkstra(ElectricVehicle &vehicle, DirectedGraphForChargingStations &graph);

    void setSourceId(unsigned int id);

    void setDestinationId(unsigned int id);

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
