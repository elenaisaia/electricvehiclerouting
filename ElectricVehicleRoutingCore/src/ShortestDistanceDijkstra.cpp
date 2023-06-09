#include "ShortestDistanceDijkstra.h"
#include <iostream>
ShortestDistanceDijkstra::ShortestDistanceDijkstra(DirectedGraphForIntersections &graph) : graph(graph) {}

void ShortestDistanceDijkstra::findDistances(unsigned int sourceId) {
    cost.clear();
    visited.clear();
    noOfArchesFromSource.clear();

    while (!queue.empty()) {
        queue.pop();
    }

    cost[sourceId].distance = 0;
    cost[sourceId].speed = 0;
    visited[sourceId] = true;
    noOfArchesFromSource[sourceId] = 0;
    NextNode source{0, 0, sourceId};
    queue.push(source);

    while (!queue.empty()) {
        unsigned int current = queue.top().nextId;
//        std::cout << current << "\n";
        queue.pop();
        visited[current] = false;
        for(auto &arch : graph.getAdjacentNodes(current)) {
//            std::cout << current << " " << arch.nextId << "\n";
            if(cost.find(arch.nextId) == cost.end() || cost[arch.nextId].distance > cost[current].distance + arch.distance) {
                cost[arch.nextId].distance = cost[current].distance + arch.distance;
                cost[arch.nextId].speed = cost[current].speed + arch.speed;
                noOfArchesFromSource[arch.nextId] = noOfArchesFromSource[current] + 1;

//                std::cout << arch.nextId << " " << arch.distance << "\n";

                if(visited.find(arch.nextId) == visited.end() || !visited.at(arch.nextId)) {
                    queue.push(arch);
                    visited[arch.nextId] = true;
//                    std::cout << arch.nextId << " " << arch.distance << "\n";
                }
            }
        }
    }
}

std::vector<NextChargingStation> ShortestDistanceDijkstra::getNextChargingStationsForChargingStation(unsigned int id) {
    findDistances(id);

    std::vector<NextChargingStation> nextStations;

    for(auto &pair : cost) {
        if (pair.first != id) {
            if(graph.containsChargingStation(pair.first)) {
                auto chargingStation = graph.getChargingStationById(pair.first);
                for (auto& charging : chargingStation.getChargingTimes()) {
                    //if(pair.first != id && pair.second.distance <= graph.getMaxDistance()) {
                    NextChargingStation nextChargingStation(chargingStation,
                            pair.second.distance,
                            pair.second.speed / noOfArchesFromSource[pair.first],
                            pair.second.distance / pair.second.speed,
                            charging.highLimit);
                        nextStations.push_back(nextChargingStation);
                }
            }
        }
    }

    return nextStations;
}
