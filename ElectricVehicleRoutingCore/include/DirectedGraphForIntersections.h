#pragma once

#include <unordered_map>
#include <string>
#include "ChargingStation.h"
#include "Intersection.h"

struct NextNode {
    double distance;
    unsigned int speed, nextId;

    bool operator<(const NextNode &rhs) const;

    bool operator>(const NextNode &rhs) const;

    bool operator<=(const NextNode &rhs) const;

    bool operator>=(const NextNode &rhs) const;
};

class DirectedGraphForIntersections {
public:
    DirectedGraphForIntersections() = default;

    DirectedGraphForIntersections(const DirectedGraphForIntersections& other) = delete;
    DirectedGraphForIntersections& operator=(const DirectedGraphForIntersections& other) = delete;

    DirectedGraphForIntersections(DirectedGraphForIntersections&& other) = default;
    DirectedGraphForIntersections& operator=(DirectedGraphForIntersections&& other) = default;

    unsigned int getVertexes() const;

    unsigned int getArches() const;

    const std::unordered_map<unsigned int, std::vector<NextNode>> &getAdjacencyList() const;

    const std::unordered_map<unsigned int, ChargingStation> &getChargingStationList() const;

    const std::unordered_map<unsigned int, Intersection> &getIntersectionList() const;

    void addChargingStationToChargingStationList(const ChargingStation& chargingStation);

    void addIntersectionToIntersectionList(const Intersection& intersection);

    void addToAdjacencyList(unsigned int sourceId, unsigned int destinationId, double distance, unsigned int speed);

    std::vector<NextNode> getAdjacentNodes(unsigned int id);

    Intersection getIntersectionById(unsigned int id);

    ChargingStation getChargingStationById(unsigned int id);

    bool containsChargingStation(unsigned int id);

    double getMaxDistance() const;

    static DirectedGraphForIntersections generateGraph(unsigned int noOfChargingStations, unsigned int noOfIntersections, double maxDistance, const std::string& fileName);

    static DirectedGraphForIntersections readGraphFromFile(const std::string& fileName);

    void setArches(unsigned int arches);

    void incrementArches();

    unsigned int getNoOfChargingStations();

private:
    unsigned int vertexes;
    unsigned int arches;
    double maxDistance;
    std::unordered_map<unsigned int, std::vector<NextNode> > adjacencyList;
    std::unordered_map<unsigned int, ChargingStation> chargingStationList;
    std::unordered_map<unsigned int, Intersection> intersectionList;


    DirectedGraphForIntersections(double maxDistance, unsigned int vertexes);

    void writeGraphToFile(const std::string& fileName) const;
    //void generateArchWithProbability(unsigned int sourceId, unsigned int destinationId, double distance);

    static double euclidean_distance(int x, int y, unsigned int x1, unsigned int y1);
    static double fRand(double fMin, double fMax);
    static int iRand(int iMin, int iMax);
};
