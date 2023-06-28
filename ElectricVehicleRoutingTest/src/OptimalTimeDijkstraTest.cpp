#include "OptimalTimeDijkstraTest.h"
#include <OptimalTimeDijkstra.h>
#include <ShortestDistanceDijkstra.h>
#include <cassert>
#include <iostream>

void OptimalTimeDijkstraTest::runTests()
{
	ElectricVehicle vehicle(49, Normal, 75, 0.1);
	vehicle.addCost(0, 30, 15);
	vehicle.addCost(30, 60, 10);
	vehicle.addCost(60, 80, 15);
	vehicle.addCost(80, 100, 25);
	vehicle.addCost(100, 130, 35);

	DirectedGraphForIntersections smallgraph = DirectedGraphForIntersections::readGraphFromFile("smallgraph.txt");
	ShortestDistanceDijkstra distanceDijkstra(smallgraph);
	DirectedGraphForChargingStations graph(5, 6);

	ChargingStation cs0(0, 100, 0);
	ChargingStation cs1(1, 100, 75);
	ChargingStation cs2(2, 100, 50);
	ChargingStation s(6, 0, 50);
	ChargingStation d(7, 200, 50);
	graph.addChargingStationToVertexList(cs0);
	graph.addChargingStationToVertexList(cs1);
	graph.addChargingStationToVertexList(cs2);
	graph.addChargingStationToVertexList(s);
	graph.addChargingStationToVertexList(d);

	auto distancesFrom0 = distanceDijkstra.getNextChargingStationsForChargingStation(0);
	auto distancesFrom1 = distanceDijkstra.getNextChargingStationsForChargingStation(1);
	auto distancesFrom2 = distanceDijkstra.getNextChargingStationsForChargingStation(2);
	auto distancesFrom6 = distanceDijkstra.getNextChargingStationsForChargingStation(6);
	graph.setAdjacentStations(0, distancesFrom0);
	graph.setAdjacentStations(1, distancesFrom1);
	graph.setAdjacentStations(2, distancesFrom2);
	graph.setAdjacentStations(6, distancesFrom6);
	
	NextChargingStation nc0d(d, 100.125, 70, 100.125/70, 0);
	NextChargingStation nc1d(d, 103.0776, 70, 103.0776/70,0);
	NextChargingStation nc2d(d, 100, 50, 100/50, 0);
	graph.addNextChargingStation(cs0, nc0d);
	graph.addNextChargingStation(cs1, nc1d);
	graph.addNextChargingStation(cs2, nc2d);

	OptimalTimeDijkstra timeDijkstra(vehicle, graph);

	timeDijkstra.setSourceId(s.getId());
	timeDijkstra.setDestinationId(d.getId());

	//assert(abs(timeDijkstra.findCost() - 3.17647) < 0.0001);
	//std::cout << timeDijkstra.findCost();
	
	OptimalRoute route = timeDijkstra.findCost();
	for (auto& station : route.path) {
		std::cout << station << "\n";
	}

	for (auto& station : route.stoppingPoints) {
		std::cout << station.id << " " << station.timeBeforeStop << " " << station.batteryPercentageBeforeStop
			<< " " << station.timeAfterStop << " " << station.batteryPercentageAfterStop << "\n";
	}
}
