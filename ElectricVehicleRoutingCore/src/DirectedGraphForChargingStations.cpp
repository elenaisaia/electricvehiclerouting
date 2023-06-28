#include "DirectedGraphForChargingStations.h"

DirectedGraphForChargingStations::DirectedGraphForChargingStations(unsigned int vertexes, unsigned int arches) : vertexes(vertexes), arches(arches) {}

unsigned int DirectedGraphForChargingStations::getVertexes() const {
    return vertexes;
}

unsigned int DirectedGraphForChargingStations::getArches() const {
    return arches;
}

const std::unordered_map<unsigned int, ChargingStation> &DirectedGraphForChargingStations::getVertexList() const {
    return vertexList;
}

void DirectedGraphForChargingStations::addChargingStationToVertexList(ChargingStation chargingStation) {
    vertexList[chargingStation.getId()] = chargingStation;
    vertexes++;
}

std::unordered_map<ChargingStation, std::vector<NextChargingStation>> DirectedGraphForChargingStations::getAdjacencyList() const {
    return adjacencyList;
}

void DirectedGraphForChargingStations::addNextChargingStation(const ChargingStation& chargingStation, const NextChargingStation& nextChargingStation) {
    adjacencyList[chargingStation].emplace_back(nextChargingStation);
    arches++;
}

std::vector<NextChargingStation> DirectedGraphForChargingStations::getAdjacentStations(ChargingStation chargingStation) {
//    return adjacencyList.at(chargingStation);
    return adjacencyList[chargingStation];
}

ChargingStation DirectedGraphForChargingStations::getVertexById(unsigned int id) {
    return vertexList.at(id);
}

void
DirectedGraphForChargingStations::setVertexList(const std::unordered_map<unsigned int, ChargingStation> &chargingStationList) {
    vertexList = chargingStationList;
    vertexes = vertexList.size();
}

void DirectedGraphForChargingStations::setAdjacentStations(unsigned int id, const std::vector<NextChargingStation>& nextChargingStationList) {
    adjacencyList[vertexList[id]] = nextChargingStationList;
    arches += nextChargingStationList.size();
}
