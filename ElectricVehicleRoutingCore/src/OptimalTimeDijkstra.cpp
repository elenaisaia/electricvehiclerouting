#include <iostream>
#include "OptimalTimeDijkstra.h"

OptimalTimeDijkstra::OptimalTimeDijkstra(ElectricVehicle &vehicle, DirectedGraphForChargingStations &graph)
        : vehicle(vehicle), graph(graph), sourceId(0), destinationId(0) {}

void OptimalTimeDijkstra::setSourceId(unsigned int id)
{
    sourceId = id;
}

void OptimalTimeDijkstra::setDestinationId(unsigned int id)
{
    destinationId = id;
}

OptimalRoute OptimalTimeDijkstra::findCost() {
    auto sourcePair = IdPair{ sourceId, vehicle.getBatteryPercentage() };
    cost[sourcePair] = 0;
    costBeforeCharging[sourcePair] = 0;
    batteryBeforeCharging[sourcePair] = 0;
    visited[sourcePair] = true;
    NextChargingStation source(graph.getVertexById(sourceId), 0, 1000, 0, vehicle.getBatteryPercentage());
    queue.push(source);

    while (!queue.empty()) {
        ChargingStation current = queue.top().getChargingStation();
        unsigned int currentMaxBatteryPercent = queue.top().getMaxBatteryPercent();
        auto currentPair = IdPair{ current.getId(), currentMaxBatteryPercent };
        queue.pop();
        visited[currentPair] = false;
        for(auto &arch : graph.getAdjacentStations(current)) {
            ChargingStation next = arch.getChargingStation();

            
            if(next.getId() == destinationId || next.isCompatibleWith(vehicle)) {
                double vehicleCostPerTimeUnit = vehicle.getCostPerTimeUnit(arch.getAvgSpeed());
                double batteryPercentageBeforeCharging = currentPair.maxBatteryPercentage - vehicleCostPerTimeUnit * arch.getTime();

                if(batteryPercentageBeforeCharging >= 20 || batteryPercentageBeforeCharging >= 10 && next.getId() != destinationId) {
                    double chargingTime = next.getChargingTime(batteryPercentageBeforeCharging, arch.getMaxBatteryPercent(), vehicle.getOnePercentChargingTime());

                    auto newCost = cost[currentPair] + arch.getTime() + chargingTime;
                    auto nextPair = IdPair{ next.getId(), arch.getMaxBatteryPercent() };
                    //if(cost.find(nextPair) == cost.end() || cost[nextPair] > newCost) {
                    if(cost[nextPair] == NULL || cost[nextPair] > newCost) {
                        cost[nextPair] = newCost;
                        parent[nextPair] = currentPair;

                        costBeforeCharging[nextPair] = cost[currentPair] + arch.getTime();
                        batteryBeforeCharging[nextPair] = batteryPercentageBeforeCharging;

                        //if(visited.find(nextPair) == visited.end() || !visited[nextPair]) {
                        if(visited[nextPair] == NULL || !visited[nextPair]) {
                            queue.push(arch);
                            visited[nextPair] = true;
                        }
                    }
                }
            }
        }
    }

    /*for (auto& elem : cost) {
        std::cout << elem.first.id << " " << elem.first.maxBatteryPercentage << "; cost: " << elem.second 
            << "; parinte: " << parent[elem.first].id << " " << parent[elem.first].maxBatteryPercentage << "\n";
    }*/

    IdPair destinationPair{ destinationId, 100 };

    //aici se creaza ruta transmisa utilizatorului parcurgand drumul inapoi in vectorul de parinti de la destinatie la sursa si culegand datele dorite
    OptimalRoute route;

    IdPair current = destinationPair;
    route.path.push_front(destinationId);
    route.stoppingPoints.push_front(StoppingPoints{ destinationId, costBeforeCharging[current], cost[destinationPair], batteryBeforeCharging[destinationPair], batteryBeforeCharging[destinationPair] });

    while (current != sourcePair) {
        current = parent[current];
        route.path.push_front(current.id);
        route.stoppingPoints.push_front(StoppingPoints{ current.id, costBeforeCharging[current], cost[current], batteryBeforeCharging[current], current.maxBatteryPercentage});
    }

    return route;
}
