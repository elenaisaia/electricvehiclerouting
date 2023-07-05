#pragma once

#include "DirectedGraphForIntersections.h"
#include "DirectedGraphForChargingStations.h"
#include <ShortestDistanceDijkstra.h>
#include <OptimalTimeDijkstra.h>

class Service {
public:
	Service() = default;

	Service(const Service& other) = delete;
	Service& operator=(const Service& other) = delete;

	void readVehicleFromFile(std::string filename);

	ElectricVehicle& getVehicle();

	DirectedGraphForIntersections& getInitialGraph(std::string filename);

	DirectedGraphForIntersections& generateInitialGraph(unsigned int noOfChargingStations, unsigned int noOfIntersections, double maxDistance, std::string filename);

	void initChargingStationGraph();

	DirectedGraphForChargingStations& getChargingStationGraph();

	OptimalRoute findPath(unsigned int sourceId, unsigned int destinationId);

private:
	ElectricVehicle vehicle;
	DirectedGraphForIntersections initialGraph;
	DirectedGraphForChargingStations chargingStationGraph;
	ShortestDistanceDijkstra distanceDijkstra{ initialGraph };
	OptimalTimeDijkstra timeDijkstra{ vehicle, chargingStationGraph };
};
