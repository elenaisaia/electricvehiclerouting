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

double OptimalTimeDijkstra::findCost() {
    auto sourcePair = IdPair{ sourceId, vehicle.getBatteryPercentage() };
    cost[sourcePair] = 0;
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

    IdPair destinationPair{ destinationId, 0 };
    return cost[destinationPair];
}

//double OptimalTimeDijkstra::findCost() {
//    cost[sourceId] = 0;
//    visited[sourceId] = true;
//    NextChargingStation source(graph.getVertexById(sourceId), 0, 1000, 0);
//    queue.push(source);
//
//    while (!queue.empty()) {
//        ChargingStation current = queue.top().getChargingStation();
//        queue.pop();
//        visited[current.getId()] = false;
//        for (auto& arch : graph.getAdjacentStations(current)) {
//            ChargingStation next = arch.getChargingStation();
//
//
//            if (next.getId() == destinationId || next.isCompatibleWith(vehicle)) {
//                double vehicleCostPerTimeUnit = vehicle.getCostPerTimeUnit(arch.getAvgSpeed());
//                double finalBatteryPercentage;
//                if (current.getId() == sourceId) {
//                    finalBatteryPercentage = vehicle.getBatteryPercentage();
//                }
//                else {
//                    finalBatteryPercentage = 100;
//                }
//                finalBatteryPercentage -= vehicleCostPerTimeUnit * arch.getTime();
//
//                if (finalBatteryPercentage >= 20 || finalBatteryPercentage >= 10 && next.getId() != destinationId) {
//                    double timeForFullCharge = (100 - finalBatteryPercentage) * std::min(vehicle.getOnePercentChargingTime(),
//                        next.getOnePercentChargingTime());
//
//                    auto newTime = cost.at(current.getId()) + arch.getTime() + timeForFullCharge;
//                    if (cost.find(next.getId()) == cost.end() || cost.at(next.getId()) > newTime) {
//                        cost[next.getId()] = newTime;
//                        parent[next.getId()] = current.getId();
//                        if (visited.find(next.getId()) == visited.end() || !visited.at(next.getId())) {
//                            queue.push(arch);
//                            visited[next.getId()] = true;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    parent[sourceId] = 99999;
//    for (auto elem : cost) {
//        std::cout << elem.first << ": cost=" << elem.second << " parent=" << parent.at(elem.first) << "\n";
//    }
//
//    return cost.at(destinationId);
//}
