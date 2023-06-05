#pragma once

#include <queue>
#include "DirectedGraphForChargingStations.h"
#include "ElectricVehicle.h"

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
    std::unordered_map<unsigned int, double> cost;
    std::unordered_map<unsigned int, unsigned int> parent;
    std::unordered_map<unsigned int, bool> visited;
};
