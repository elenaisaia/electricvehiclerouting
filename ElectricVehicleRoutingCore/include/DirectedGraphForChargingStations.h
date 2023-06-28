#pragma once

#include <vector>
#include <unordered_map>
#include "NextChargingStation.h"


namespace std {
    template<>
    struct hash<ChargingStation> {
        auto operator()(const ChargingStation &chargingStation) const -> size_t {
            return hash<unsigned int>()(chargingStation.getId());
        }
    };
}

class DirectedGraphForChargingStations {
public:
    DirectedGraphForChargingStations() = default;

    DirectedGraphForChargingStations(const DirectedGraphForChargingStations& other) = delete;
    DirectedGraphForChargingStations& operator=(const DirectedGraphForChargingStations& other) = delete;

    DirectedGraphForChargingStations(DirectedGraphForChargingStations&& other) = default;
    DirectedGraphForChargingStations& operator=(DirectedGraphForChargingStations&& other) = default;

    DirectedGraphForChargingStations(unsigned int vertexes, unsigned int arches);

    unsigned int getVertexes() const;

    unsigned int getArches() const;

    const std::unordered_map<unsigned int, ChargingStation> &getVertexList() const;

    void addChargingStationToVertexList(ChargingStation chargingStation);

    void setVertexList(const std::unordered_map<unsigned int, ChargingStation> &chargingStationList);

    std::unordered_map<ChargingStation, std::vector<NextChargingStation>> getAdjacencyList() const;

    void addNextChargingStation(const ChargingStation& chargingStation, const NextChargingStation& nextChargingStation);

    void setAdjacentStations(unsigned int id, const std::vector<NextChargingStation>& nextChargingStationList);

    std::vector<NextChargingStation> getAdjacentStations(ChargingStation chargingStation);

    ChargingStation getVertexById(unsigned int id);

private:
    unsigned int vertexes;
    unsigned int arches;
    std::unordered_map<ChargingStation, std::vector<NextChargingStation> > adjacencyList;
    std::unordered_map<unsigned int, ChargingStation> vertexList;
};
