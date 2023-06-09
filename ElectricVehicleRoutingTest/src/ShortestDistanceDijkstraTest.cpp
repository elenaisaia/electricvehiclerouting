#include "ShortestDistanceDijkstraTest.h"
#include <ShortestDistanceDijkstra.h>
#include <cassert>

void ShortestDistanceDijkstraTest::runTests()
{
	DirectedGraphForIntersections graph = DirectedGraphForIntersections::readGraphFromFile("smallgraph.txt");
	ShortestDistanceDijkstra distanceDijkstra(graph);

	auto distancesFrom0 = distanceDijkstra.getNextChargingStationsForChargingStation(0);
	assert(distancesFrom0.size() == 0);

	auto distancesFrom1 = distanceDijkstra.getNextChargingStationsForChargingStation(1);
	assert(distancesFrom1.size() == 0);

	auto distancesFrom2 = distanceDijkstra.getNextChargingStationsForChargingStation(2);
	assert(distancesFrom2.size() == 0);

	auto distancesFrom3 = distanceDijkstra.getNextChargingStationsForChargingStation(3);
	assert(distancesFrom3.size() == 15);

	auto distancesFrom4 = distanceDijkstra.getNextChargingStationsForChargingStation(4);
	assert(distancesFrom4.size() == 0);

	auto distancesFrom5 = distanceDijkstra.getNextChargingStationsForChargingStation(5);
	assert(distancesFrom5.size() == 5);

	auto distancesFrom6 =  distanceDijkstra.getNextChargingStationsForChargingStation(6);
	assert(distancesFrom6.size() == 15);

	auto distancesFrom7 = distanceDijkstra.getNextChargingStationsForChargingStation(7);
	assert(distancesFrom7.size() == 0);
}
