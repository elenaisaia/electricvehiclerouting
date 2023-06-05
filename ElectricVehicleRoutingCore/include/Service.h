#pragma once

#include "DirectedGraphForIntersections.h"
#include "DirectedGraphForChargingStations.h"
#include <memory>

class Service {
public:
	Service();

	Service(const Service& other) = delete;
	Service& operator=(const Service& other) = delete;

	DirectedGraphForChargingStations getGraph();

	DirectedGraphForIntersections& getInitialGraph();
	
private:
	DirectedGraphForIntersections initialGraph;
	DirectedGraphForChargingStations chargingStationGraph;

};
