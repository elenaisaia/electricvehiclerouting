#include "ServiceTest.h"
#include <Service.h>
#include <cassert>
#include <iostream>

void ServiceTest::runTests()
{
	Service service;

	service.readVehicleFromFile("vehicle.txt");
	assert(service.getVehicle().getId() == 49);
	assert(service.getVehicle().getChargerType() == Normal);
	assert(service.getVehicle().getBatteryPercentage() == 75);
	assert(abs(service.getVehicle().getOnePercentChargingTime() - 0.1) < 0.0001);

	auto& initialGraph = service.getInitialGraph("smallgraph.txt");
	assert(initialGraph.getVertexes() == 8);
	assert(initialGraph.getArches() == 14);


	service.initChargingStationGraph();
	auto& chargingStationGraph = service.getChargingStationGraph();
	assert(chargingStationGraph.getVertexes() == 3);
	assert(chargingStationGraph.getArches() == 0);

	//assert(abs(service.findCost(6, 7) - 3.17647) < 0.0001);
}
