#include "DirectedGraphForIntersectionsTest.h"
#include <DirectedGraphForIntersections.h>
#include <cassert>

void DirectedGraphForIntersectionsTest::runTests()
{
	DirectedGraphForIntersections graph = DirectedGraphForIntersections::readGraphFromFile("smallgraph.txt");
	assert(graph.getVertexes() == 8);
	assert(graph.getArches() == 14);
	assert(graph.getMaxDistance() == 200);

	assert(graph.getNoOfChargingStations() == 3);
	assert(graph.getChargingStationList().size() == 3);
	assert(graph.getIntersectionList().size() == 5);

	assert(graph.getAdjacentNodes(7).size() == 0);
	assert(graph.getAdjacentNodes(6).size() == 4);
	assert(graph.getAdjacentNodes(1).size() == 2);

	assert(graph.getChargingStationById(0).getId() == 0);
	assert(graph.getChargingStationById(0).getX() == 100);
	assert(graph.getChargingStationById(0).getY() == 0);

	assert(graph.getIntersectionById(4).getId() == 4);
	assert(graph.getIntersectionById(4).getX() == 150);
	assert(graph.getIntersectionById(4).getY() == 50);

	assert(graph.containsChargingStation(2) == true);
	assert(graph.containsChargingStation(3) == false);
	assert(graph.containsChargingStation(7) == false);

	graph.incrementArches();
	assert(graph.getArches() == 15);

	ChargingStation chargingStation(10, 1000, 1000);
	graph.addChargingStationToChargingStationList(chargingStation);
	assert(graph.getNoOfChargingStations() == 4);

	Intersection intersection(11, 1010, 1000);
	graph.addIntersectionToIntersectionList(intersection);
	assert(graph.getIntersectionList().size() == 6);

	NextNode node{ 50, 100, 11 };
	graph.addToAdjacencyList(10, 11, 50, 100);
	assert(graph.getAdjacencyList().at(10).size() == 1);
	assert(graph.getAdjacentNodes(10).at(0).nextId == 11);
	assert(graph.getAdjacentNodes(10).at(0).distance == 50);
	assert(graph.getAdjacentNodes(10).at(0).speed == 100);

	NextNode node1{ 51, 100, 11 };
	assert(node < node1);
	assert(node <= node1);
	assert(node1 > node);
	assert(node1 >= node);

	NextNode node2{ 50, 90, 11 };
	assert(node < node2);
	assert(node <= node2);
	assert(node2 > node);
	assert(node2 >= node);

	NextNode node3{ 50, 100, 20 };
	assert(node < node3);
	assert(node <= node3);
	assert(node3 > node);
	assert(node3 >= node);

	NextNode node4{ 50, 100, 11 };
	assert(node <= node4);
	assert(node4 <= node);
	assert(node4 >= node);
	assert(node >= node4);

	graph.setArches(0);
	assert(graph.getArches() == 0);
}
